/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include <QDockWidget>

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include "bin.h"
#include <QFile>
#include <QFileDialog>
#include <QDate>
#include <QDebug>



//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*测试版本，到达一定日期则不可用*/
    QString date = QDate::currentDate().toString("yyyyMMdd");
    if(date.toInt() > 20171023)
    {
        return;
    }

    ui->setupUi(this);
    serial = new QSerialPort(this);
    settings = new SettingsDialog;
    FastCmd_data = new FastCmd(this);
    pSendDialog = new CSendDialog(this);
    pRecvDialog = new CRecvDialog(this);
    pRecv35HDialog = new CRecv35HDialog(this);
    pRecv34HDialog = new CRecv34HDialog(this);
    p_GraphDialog = new CGraphDialog(this);
    this->setWindowTitle("GF_Software");

    p7373H = new C7373H(this);

    timer = new QTimer();   //新建一个QTimer对象
    timer->setInterval(60000);  //1分钟
    timer->start();    //启动定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    fileName_Grpha = "";


    i4FlagSave = 0;
    f8countGraph = 0.0;


    setCentralWidget(p7373H);

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    initActionsConnections();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData())); //收信息
    connect(FastCmd_data,SIGNAL(windowTitleChanged(QString)),this,SLOT(readAll()));
    connect(pSendDialog,SIGNAL(windowTitleChanged(QString)),this,SLOT(readAll()));
    connect(ui->actionSaveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionFastCmd,SIGNAL(triggered()),this,SLOT(onFastCmd()));

    m_FastCmd_data = new QDockWidget("FastCmd",this);               //浮动
    m_FastCmd_data->setFeatures(QDockWidget::AllDockWidgetFeatures);
    m_FastCmd_data->setAllowedAreas(Qt::AllDockWidgetAreas);
    m_FastCmd_data->setWidget(FastCmd_data);

    m_DkWgt_373H = new QDockWidget(tr("7373H_data"),this);
    m_DkWgt_373H->setFeatures(QDockWidget::AllDockWidgetFeatures);     //全部特性
    m_DkWgt_373H->setAllowedAreas(Qt::AllDockWidgetAreas);//全部特性
    m_DkWgt_373H->setWidget(p7373H);
    //addDockWidget(Qt::TopDockWidgetArea,dock);

    m_SendMsg = new QDockWidget(tr("CollectSetting"),this);
    m_SendMsg->setFeatures(QDockWidget::AllDockWidgetFeatures);     //全部特性
    m_SendMsg->setAllowedAreas(Qt::AllDockWidgetAreas);//全部特性
    m_SendMsg->setWidget(pSendDialog);

    m_RecvMsg = new QDockWidget(tr("RecvMsg"),this);
    m_RecvMsg->setFeatures(QDockWidget::NoDockWidgetFeatures);     //全部特性
    m_RecvMsg->setAllowedAreas(Qt::AllDockWidgetAreas);//全部特性
    m_RecvMsg->setWidget(pRecvDialog);

    m_Recv35HMsg = new QDockWidget(tr("Recv35HMsg"),this);
    m_Recv35HMsg->setFeatures(QDockWidget::AllDockWidgetFeatures);     //全部特性
    m_Recv35HMsg->setAllowedAreas(Qt::AllDockWidgetAreas);//全部特性
    m_Recv35HMsg->setWidget(pRecv35HDialog);

    m_Recv34HMsg = new QDockWidget(tr("Recv34HMsg"),this);
    m_Recv34HMsg->setFeatures(QDockWidget::AllDockWidgetFeatures);     //全部特性
    m_Recv34HMsg->setAllowedAreas(Qt::AllDockWidgetAreas);//全部特性
    m_Recv34HMsg->setWidget(pRecv34HDialog);

    m_Graph = new QDockWidget(tr("Graph"),this);
    m_Graph->setFeatures(QDockWidget::NoDockWidgetFeatures);     //全部特性
    m_Graph->setAllowedAreas(Qt::AllDockWidgetAreas);//全部特性
    m_Graph->setWidget(p_GraphDialog);
    //m_Graph->setSizeIncrement(832,435);



    m_FastCmd_data->hide();
    m_DkWgt_373H->hide();
    m_RecvMsg->hide();
    m_Recv34HMsg->hide();
    m_Recv35HMsg->hide();
    m_SendMsg->hide();

    this->setCentralWidget(m_Graph);
    //(Qt::BottomDockWidgetArea, m_Graph);
    //addDockWidget(Qt::BottomDockWidgetArea, m_RecvMsg);
    //addDockWidget(Qt::RightDockWidgetArea, m_Recv34HMsg);
    //addDockWidget(Qt::RightDockWidgetArea, m_Recv35HMsg);

    //将GGA 与 DHV 合并为标签页
    //tabifyDockWidget(m_Recv34HMsg, m_Recv35HMsg);

    /**********开机初始操作***************/
    openSerialPort();  //开机即连接串口
    collectStart();  //开机设置为采集模式
    this->showMaximized();



    //p_GraphDialog->readSettings();
}
MainWindow::~MainWindow()
{
    //p_GraphDialog->saveSettings();
    delete settings;
    delete ui;
}
void MainWindow::onFastCmd()
{
    m_FastCmd_data->move(this->width()/3,this->height()/3);
    m_FastCmd_data->show();
    m_FastCmd_data->setFloating(1);

}
void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}

void MainWindow::onTimerOut()
{
    collectEnd();
    timer->stop();
}

void MainWindow::closeSerialPort()
{
    serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("关于GF_Software"),
                       tr("        XXXXXX科技有限公司       \t\t \r\n\r\n"
                          "     Verson V1.0          2017-5-31        "
                          ));
}

void MainWindow::saveFile()
{
   if(0 == i4FlagSave)
   {
       QString fileName,fileName1;
       fileName.append(QString("%1_%2_%3")
                       .arg(settings->settings().name)
                       .arg(QDate::currentDate().toString("yyyyMMdd"))
                       .arg(QTime::currentTime().toString("HHmmss"))
                       );
       //fileName = QFileDialog::getSaveFileName(this, tr("Save File"), fileName, tr("Data (*.dat *.txt)"));

       fileName = QCoreApplication::applicationDirPath() + fileName + tr(".dat");

       fileName1 = fileName;
       fileName1.resize(fileName.size()-4);
       fileName_Grpha = fileName1;
       fileName1 = fileName1 + tr("Hex.dat");

       if(!fileName.isEmpty())
       {
           outFile.setFileName(fileName);
           if(!outFile.open(QIODevice::WriteOnly|QIODevice::Append))
           {
               qDebug()<<"打开文件失败"<<"\r\n";
               return;
           }
       }

       if(!fileName1.isEmpty())
       {
           outFile1.setFileName(fileName1);
           if(!outFile1.open(QIODevice::WriteOnly|QIODevice::Append))
           {
               qDebug()<<"打开文件失败"<<"\r\n";
               return;
           }
       }
       if(outFile.isOpen())
       {
           i4FlagSave = 1;  //标志位，为1时开始保存数据
           ui->actionSaveFile->setIcon(QIcon(":/images/SaveFile_Close.png"));
       }
   }
   else if(1 == i4FlagSave)
   {
        i4FlagSave =0;
        outFile.close();
        outFile1.close();
        ui->actionSaveFile->setIcon(QIcon(":/images/SaveFile.png"));
        onScreenShot(fileName_Grpha);
   }
}

void MainWindow::readAll()
{
    for(int i=0;i<10;i++)
    {
        if(FastCmd_data->m_pWidgets[i]->flag)
        {
            QByteArray strData = FastCmd_data->GetData(i);
            serial->write(strData);
            FastCmd_data->m_pWidgets[i]->flag = 0;
        }
    }

    if(pSendDialog->flag_11H)
    {
        QString strData0 = "24 42 49 4E 0B 00 01 00 01 01 00 0D 0A";
        QByteArray strData = strData0.toLocal8Bit();
        strData = QByteArray::fromHex(strData);
        serial->write(strData);
        pSendDialog->flag_11H = 0;
    }
    if(pSendDialog->flag_12H)
    {
        QString strData0[4] = {"24 42 49 4E 0C 00 01 00 00 00 00 0D 0A",  //停止模式
                               "24 42 49 4E 0C 00 01 00 01 01 00 0D 0A",  //采集模式
                               "24 42 49 4E 0C 00 01 00 02 02 00 0D 0A",  //工程模式
                               "24 42 49 4E 0C 00 01 00 03 03 00 0D 0A",  //校准模式
                              };

        QByteArray strData = strData0[pSendDialog->flag_12H-1].toLocal8Bit();
        strData = QByteArray::fromHex(strData);
        serial->write(strData);
        pSendDialog->flag_12H = 0;
    }

    if(pSendDialog->flag_13H)  //m_TAcqParam_13H  113 = 0x071  113+12=125
    {
        char data[125] = {0x24, 0x42, 0x49, 0x4E, 0x0D, 0x00, 0x71, 0x00};
        memcpy(&data[8], &pSendDialog->m_TAcqParam_13H, 125);
        u2 u2Sum = u2GetSum(&data[8], 113);
        data[121] = (i1)(u2Sum & 0xFF);
        data[122] = (i1)(u2Sum>>8 & 0xFF);
        data[123] = 0x0D;
        data[124] = 0x0A;
        serial->write(data, sizeof(data));
        pSendDialog->flag_13H = 0;
    }

    if(pSendDialog->flag_14H)
    {
        char i1Check;
        QString str[18] = {"00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F","10","11"};
        QString strData0 = "24 42 49 4E 0E 00 02 00";
        strData0 += str[(i1)pSendDialog->flag_14H];
        strData0 += str[(pSendDialog->flag_14H>>8)&0xFF];
        i1Check = (i1)pSendDialog->flag_14H + (pSendDialog->flag_14H>>8)&0xFF;
        strData0 += str[i1Check];
        strData0 += "00 0D 0A";
        QByteArray strData = strData0.toLocal8Bit();
        strData = QByteArray::fromHex(strData);
        serial->write(strData);
        pSendDialog->flag_14H = 0;
    }

    if(pSendDialog->flag_15H)
    {
        QString strData0 = "24 42 49 4E 0F 00 01 00 01 01 00 0D 0A";
        QByteArray strData = strData0.toLocal8Bit();
        strData = QByteArray::fromHex(strData);
        serial->write(strData);
        pSendDialog->flag_15H = 0;
    }

    if(pSendDialog->flag_16H)
    {
        QString strData0 = "24 42 49 4E 10 00 01 00 01 01 00 0D 0A";
        QByteArray strData = strData0.toLocal8Bit();
        strData = QByteArray::fromHex(strData);
        serial->write(strData);
        pSendDialog->flag_16H = 0;
    }
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

//! [6]

//! [7]
void MainWindow::readData()
{
    /* QByteArray data = serial->readAll();
    console->putData(data);*/

   i1 data;
   while(!serial->atEnd())
   {
       data = serial->read(1).at(0);

       if(1 == i4FlagSave)
       {
           outFile1.write(&data,1);

       }
       else if(2 == i4FlagSave)
       {
           outFile1.close();
       }
       //BIN_ParserFrame(aa);
       switch(BIN_ParserFrame(data))
       {
       case 0x73:
           memset(&g_T7373, 0, sizeof(g_T7373));
           memcpy(&g_T7373, &m_BuffRecv[8], sizeof(g_T7373));
           p7373H->Update7373H(&g_T7373);
           if(1 == i4FlagSave)
           {
               outFile.write(p7373H->MakeSave(&g_T7373));
           }
           else if(2 == i4FlagSave)
           {
               outFile.close();
           }
           break;
       case 0x1F:  //31H
           memset(&g_T31, 0, sizeof(g_T31));
           memcpy(&g_T31, &m_BuffRecv[8], sizeof(g_T31));
           pSendDialog->Update31H(&g_T31);
           if(1 == i4FlagSave)
           {
               outFile.write(pSendDialog->MakeSave(&g_T31));
           }
           else if(2 == i4FlagSave)
           {
               outFile.close();
           }
           break;

       case 0x20:  //32H
           memset(&g_T32, 0, sizeof(g_T32));
           memcpy(&g_T32, &m_BuffRecv[8], sizeof(g_T32));
           pSendDialog->Update32H(&g_T32);
           if(1 == i4FlagSave)
           {
               outFile.write(pSendDialog->MakeSave(&g_T32));
           }
           else if(2 == i4FlagSave)
           {
               outFile.close();
           }
           break;
       case 0x21:  //33H
           memset(&g_T33, 0, sizeof(g_T33));
           memcpy(&g_T33, &m_BuffRecv[8], sizeof(g_T33));

           x.push_back(f8countGraph);
           y[0].push_back(g_T33.u2RealData[0]/1.0);
           y[1].push_back(g_T33.u2RealData[1]/1.0);
           y[2].push_back(g_T33.u2RealData[2]/1.0);
           y[3].push_back(g_T33.u2RealData[3]/1.0);
           y[4].push_back(g_T33.u2RealData[4]/1.0);
           y[5].push_back(g_T33.u2RealData[5]/1.0);
           y[6].push_back(g_T33.u2RealData[6]/1.0);
           y[7].push_back(g_T33.u2RealData[7]/1.0);
           y[8].push_back(g_T33.u2RealData[8]/1.0);
           y[9].push_back(g_T33.u2RealData[9]/1.0);
           y[10].push_back(g_T33.u2RealData[10]/1.0);
           y[11].push_back(g_T33.u2RealData[11]/1.0);
           y[12].push_back(g_T33.u2RealData[12]/1.0);
           y[13].push_back(g_T33.u2RealData[13]/1.0);
           y[14].push_back(g_T33.u2RealData[14]/1.0);
           y[15].push_back(g_T33.u2RealData[15]/1.0);



           p_GraphDialog->DrawGraph(x,y);
           f8countGraph += 0.1;

           pRecvDialog->Update33H(&g_T33);
           if(1 == i4FlagSave)
           {
               outFile.write(pRecvDialog->MakeSave(&g_T33));
           }
           else if(2 == i4FlagSave)
           {
               outFile.close();
           }
           break;

       case 0x22:  //34H
           memset(&g_T34, 0, sizeof(g_T34));
           memcpy(&g_T34, &m_BuffRecv[8], sizeof(g_T34));
           pRecv34HDialog->Update34H(&g_T34);
           if(1 == i4FlagSave)
           {
               outFile.write(pRecv34HDialog->MakeSave(&g_T34));
           }
           else if(2 == i4FlagSave)
           {
               outFile.close();
           }
           break;

       case 0x23:  //35H
           memset(&g_T35, 0, sizeof(g_T35));
           memcpy(&g_T35, &m_BuffRecv[8], sizeof(g_T35));
           pRecv35HDialog->Update35H(&g_T35);
           if(1 == i4FlagSave)
           {
               outFile.write(pRecv35HDialog->MakeSave(&g_T35));
           }
           else if(2 == i4FlagSave)
           {
               outFile.close();
           }
           break;

       case 0x24:  //36H
           memset(&g_T36, 0, sizeof(g_T36));
           memcpy(&g_T36, &m_BuffRecv[8], sizeof(g_T36));
           pSendDialog->Update36H(&g_T36);
           if(1 == i4FlagSave)
           {
               outFile.write(pSendDialog->MakeSave(&g_T36));
           }
           else if(2 == i4FlagSave)
           {
               outFile.close();
           }
           break;

        default:
            break;

       }
   }

}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    //connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clear_All()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionCollectSetting, SIGNAL(triggered()), this, SLOT(collectSetting()));
    connect(ui->actionCollectStart, SIGNAL(triggered()), this, SLOT(collectStart()));
    connect(ui->actionCollectEnd, SIGNAL(triggered()), this, SLOT(collectEnd()));
    connect(ui->actionScreenShot, SIGNAL(triggered()), this, SLOT(onScreenShot1()));

}
void MainWindow::clear_All()
{
    p7373H->clear_7373H();
    pSendDialog->clear_31H();
    pSendDialog->clear_32H();
    pRecvDialog->clear_33H();
    pRecv34HDialog->clear_34H();
    pRecv35HDialog->clear_35H();
    pSendDialog->clear_36H();

    p_GraphDialog->clearGraph();
    x.clear();
    for(int j=0; j<16;j++)
    {
        y[j].clear();
    }
    f8countGraph = 0;


}
void MainWindow::collectSetting()
{
    m_SendMsg->move(this->width()/3,this->height()/3);
    m_SendMsg->show();
    m_SendMsg->setFloating(1);
}
void MainWindow::collectStart()
{
    /*每次开始采集（1分钟）前，清除曲线*/
    p_GraphDialog->clearGraph();
    x.clear();
    for(int j=0; j<16;j++)
    {
        y[j].clear();
    }
    f8countGraph = 0;

    //p_GraphDialog->DrawGraph();
    QString strData0 = "24 42 49 4E 0C 00 01 00 01 01 00 0D 0A";  //开始采集
    QByteArray strData = strData0.toLocal8Bit();
    strData = QByteArray::fromHex(strData);
    serial->write(strData);
    ui->actionCollectStart->setEnabled(false);
    ui->actionCollectEnd->setEnabled(true);
    timer->start();
    saveFile(); //开机即开始保存数据，一分钟后停止保存，数据有一份原始数(16进制)，一份可读数据，一张截图
}
void MainWindow::onScreenShot1()
{
    QString fileName;
    QPixmap pix, bmp;
    //pix =bmp.grabWindow(QApplication::desktop()->winId(),0,0,frameGeometry().width(),frameGeometry().height());
    pix =bmp.grabWindow(QApplication::desktop()->winId(),geometry().x(),geometry().y()+90,geometry().width(),geometry().height()-90);
    fileName= QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss")  + ".bmp";//通过时间命名文件
    if (pix.isNull())
    {
        QMessageBox::information(this, "Error", "截屏失败 !", QMessageBox::Ok);
    }
    else
    {
        if(!pix.save("../"+fileName,"BMP"))
        {
            QMessageBox::information(this, "Right", "保存错误 !", QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this, "Grab", "保存成功!",QMessageBox::Ok);
        }
    }
}

void MainWindow::onScreenShot(QString fileName)
{
    //QString fileName;
    QPixmap pix, bmp;
    //pix =bmp.grabWindow(QApplication::desktop()->winId(),0,0,frameGeometry().width(),frameGeometry().height());
    pix =bmp.grabWindow(QApplication::desktop()->winId(),geometry().x(),geometry().y()+90,geometry().width(),geometry().height()-90);
    fileName += tr(".bmp");//通过时间命名文件
    if (pix.isNull())
    {
        QMessageBox::information(this, "Error", "截屏失败 !", QMessageBox::Ok);
    }
    else
    {
        if(!pix.save(fileName,"BMP"))
        {
            QMessageBox::information(this, "Right", "保存错误 !", QMessageBox::Ok);
        }
        else
        {
            QMessageBox::information(this, "Grab", "保存成功!",QMessageBox::Ok);
        }
    }

}

void MainWindow::collectEnd()
{
    QString strData0 = "24 42 49 4E 0C 00 01 00 00 00 00 0D 0A";  //停止采集
    QByteArray strData = strData0.toLocal8Bit();
    strData = QByteArray::fromHex(strData);
    serial->write(strData);
    ui->actionCollectEnd->setEnabled(false);
    ui->actionCollectStart->setEnabled(true);
    saveFile(); //开机即开始保存数据，一分钟后停止保存，数据有一份原始数(16进制)，一份可读数据，一张截图
}

u2 MainWindow::u2GetSum(const char *p, int nLen)
{
    u2 u2Sum = 0;
    for(int i=0; i<nLen; i++)
    {
        u2Sum += p[i];
    }
    return u2Sum;
}
