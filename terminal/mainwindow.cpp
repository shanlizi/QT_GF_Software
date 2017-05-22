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
#include<QDockWidget>

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
//! [0]
//!
    ui->setupUi(this);
    serial = new QSerialPort(this);
    settings = new SettingsDialog;

    p7373H = new C7373H(this);


    i4FlagSave = 0;


    setCentralWidget(p7373H);

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    initActionsConnections();

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData())); //收信息
    connect(ui->actionSaveFile, SIGNAL(triggered()), this, SLOT(saveFile()));


    m_DkWgt_373H = new QDockWidget(tr("7373H_data"),this);
    m_DkWgt_373H->setFeatures(QDockWidget::AllDockWidgetFeatures);     //全部特性
    m_DkWgt_373H->setAllowedAreas(Qt::AllDockWidgetAreas);//全部特性
    m_DkWgt_373H->setWidget(p7373H);
    //addDockWidget(Qt::TopDockWidgetArea,dock);



    this->setCentralWidget(m_DkWgt_373H);
    //addDockWidget(Qt::BottomDockWidgetArea, m_GGA_data);

    //将GGA 与 DHV 合并为标签页
    //tabifyDockWidget(m_GGA_data, m_DHV_data);

}


MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

//! [4]
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
//! [4]

//! [5]
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
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
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
       fileName = QFileDialog::getSaveFileName(this, tr("Save File"), fileName, tr("Data (*.dat *.txt)"));

       fileName1 = fileName;
       fileName1.resize(fileName.size()-4);
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
}
void MainWindow::clear_All()
{
    p7373H->clear_7373H();
}
