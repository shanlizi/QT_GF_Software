#include "crecv35hdialog.h"
#include "ui_crecv35hdialog.h"

CRecv35HDialog::CRecv35HDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRecv35HDialog)
{
    ui->setupUi(this);
    ui->tableWidget_35H->horizontalHeader()->show();
    ui->tableWidget_35H->verticalHeader()->show();
}

CRecv35HDialog::~CRecv35HDialog()
{
    delete ui;
}
void CRecv35HDialog::Update35H(const T35H *p35H)
{
    ui->tableWidget_35H->setRowCount(4);
    ui->tableWidget_35H->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget_35H->insertRow(0);

    ui->tableWidget_35H->setItem(0,0,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[0])));
    ui->tableWidget_35H->setItem(0,1,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[1])));
    ui->tableWidget_35H->setItem(0,2,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[2])));
    ui->tableWidget_35H->setItem(0,3,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[3])));
    ui->tableWidget_35H->setItem(0,4,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[4])));
    ui->tableWidget_35H->setItem(0,5,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[5])));
    ui->tableWidget_35H->setItem(0,6,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[6])));
    ui->tableWidget_35H->setItem(0,7,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[7])));
    ui->tableWidget_35H->setItem(0,8,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[8])));
    ui->tableWidget_35H->setItem(0,9,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[9])));
    ui->tableWidget_35H->setItem(0,10,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[10])));
    ui->tableWidget_35H->setItem(0,11,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[11])));
    ui->tableWidget_35H->setItem(0,12,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[12])));
    ui->tableWidget_35H->setItem(0,13,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[13])));
    ui->tableWidget_35H->setItem(0,14,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[14])));
    ui->tableWidget_35H->setItem(0,15,new QTableWidgetItem(QString("%1").arg(p35H->u2CheckData[15])));


    ui->tableWidget_35H->resizeColumnsToContents();
    ui->tableWidget_35H->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_35H->show();


}
void CRecv35HDialog::clear_35H()
{
    ui->tableWidget_35H->clearContents();
}
QByteArray CRecv35HDialog::MakeSave(const T35H *p35H)
{
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("35H:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16\r\n")
                    .arg(p35H->u2CheckData[0])
                    .arg(p35H->u2CheckData[1])
                    .arg(p35H->u2CheckData[2])
                    .arg(p35H->u2CheckData[3])
                    .arg(p35H->u2CheckData[4])
                    .arg(p35H->u2CheckData[5])
                    .arg(p35H->u2CheckData[6])
                    .arg(p35H->u2CheckData[7])
                    .arg(p35H->u2CheckData[8])
                    .arg(p35H->u2CheckData[9])
                    .arg(p35H->u2CheckData[10])
                    .arg(p35H->u2CheckData[11])
                    .arg(p35H->u2CheckData[12])
                    .arg(p35H->u2CheckData[13])
                    .arg(p35H->u2CheckData[14])
                    .arg(p35H->u2CheckData[15])
            );
    return BtAryMsg;

}
