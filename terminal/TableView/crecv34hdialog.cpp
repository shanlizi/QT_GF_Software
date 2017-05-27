#include "crecv34hdialog.h"
#include "ui_crecv34hdialog.h"

CRecv34HDialog::CRecv34HDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRecv34HDialog)
{
    ui->setupUi(this);
    ui->tableWidget_34H->horizontalHeader()->show();
    ui->tableWidget_34H->verticalHeader()->show();
}

CRecv34HDialog::~CRecv34HDialog()
{
    delete ui;
}

void CRecv34HDialog::Update34H(const T34H *p34H)
{
    ui->tableWidget_34H->setRowCount(4);
    ui->tableWidget_34H->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget_34H->insertRow(0);

    QString str1,str2;
    if(0 == p34H->i1Hatch)
    {
        str1 = "闭合";
    }
    else if(1 == p34H->i1Hatch)
    {
        str1 = "开启";
    }
    else
    {
        str1 = "错误";
    }

    if(0 == p34H->i1Hatch)
    {
        str2 = "熄灭";
    }
    else if(1 == p34H->i1Hatch)
    {
        str2 = "点亮";
    }
    else
    {
        str2 = "错误";
    }

    ui->tableWidget_34H->setItem(0,0,new QTableWidgetItem(QString("%1").arg(p34H->f4MonitorData[0],0,'f',3)));
    ui->tableWidget_34H->setItem(0,1,new QTableWidgetItem(QString("%1").arg(p34H->f4MonitorData[1],0,'f',3)));
    ui->tableWidget_34H->setItem(0,2,new QTableWidgetItem(QString("%1").arg(p34H->f4MonitorData[2],0,'f',3)));
    ui->tableWidget_34H->setItem(0,3,new QTableWidgetItem(QString("%1").arg(p34H->f4MonitorData[3],0,'f',3)));
    ui->tableWidget_34H->setItem(0,4,new QTableWidgetItem(QString("%1").arg(p34H->f4MonitorData[4],0,'f',3)));
    ui->tableWidget_34H->setItem(0,5,new QTableWidgetItem(QString("%1").arg(str1)));
    ui->tableWidget_34H->setItem(0,6,new QTableWidgetItem(QString("%1").arg(str2)));

    ui->tableWidget_34H->resizeColumnsToContents();
    ui->tableWidget_34H->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_34H->show();
}
void CRecv34HDialog::clear_34H()
{
    ui->tableWidget_34H->clearContents();
}
QByteArray CRecv34HDialog::MakeSave(const T34H *p34H)
{
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("34H:%1 %2 %3 %4 %5 %6 %7\r\n")
                    .arg(p34H->f4MonitorData[0])
                    .arg(p34H->f4MonitorData[1])
                    .arg(p34H->f4MonitorData[2])
                    .arg(p34H->f4MonitorData[3])
                    .arg(p34H->f4MonitorData[4])
                    .arg(p34H->i1Hatch)
                    .arg(p34H->i1LED)
            );
    return BtAryMsg;
}
