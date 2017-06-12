#include "crecvdialog.h"
#include "ui_crecvdialog.h"

CRecvDialog::CRecvDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRecvDialog)
{
    ui->setupUi(this);
    ui->tableWidget_33H_1->horizontalHeader()->show();
    ui->tableWidget_33H_1->verticalHeader()->show();
    ui->tableWidget_33H_2->horizontalHeader()->show();
    ui->tableWidget_33H_2->verticalHeader()->show();
}

CRecvDialog::~CRecvDialog()
{
    delete ui;
}
void CRecvDialog::Update33H(const T33H *p33H)
{
    ui->tableWidget_33H_1->setRowCount(4);
    ui->tableWidget_33H_1->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget_33H_1->insertRow(0);
    ui->tableWidget_33H_2->setRowCount(4);
    ui->tableWidget_33H_2->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget_33H_2->insertRow(0);


    ui->label_AcqTime->setText(QString("%1").arg(p33H->u2Time));
    ui->label_17ADC->setText(QString("%1").arg(GetComplement(p33H->u2OriginData[16])));
    ui->label_18ADC->setText(QString("%1").arg(GetComplement(p33H->u2OriginData[17])));
    ui->tableWidget_33H_1->setItem(0,0,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[0]))));
    ui->tableWidget_33H_1->setItem(0,1,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[1]))));
    ui->tableWidget_33H_1->setItem(0,2,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[2]))));
    ui->tableWidget_33H_1->setItem(0,3,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[3]))));
    ui->tableWidget_33H_1->setItem(0,4,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[4]))));
    ui->tableWidget_33H_1->setItem(0,5,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[5]))));
    ui->tableWidget_33H_1->setItem(0,6,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[6]))));
    ui->tableWidget_33H_1->setItem(0,7,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[7]))));
    ui->tableWidget_33H_1->setItem(0,8,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[8]))));
    ui->tableWidget_33H_1->setItem(0,9,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[9]))));
    ui->tableWidget_33H_1->setItem(0,10,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[10]))));
    ui->tableWidget_33H_1->setItem(0,11,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[11]))));
    ui->tableWidget_33H_1->setItem(0,12,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[12]))));
    ui->tableWidget_33H_1->setItem(0,13,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[13]))));
    ui->tableWidget_33H_1->setItem(0,14,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[14]))));
    ui->tableWidget_33H_1->setItem(0,15,new QTableWidgetItem(QString("%1").arg(GetComplement(p33H->u2OriginData[15]))));

    ui->tableWidget_33H_2->setItem(0,0,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[0])));
    ui->tableWidget_33H_2->setItem(0,1,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[1])));
    ui->tableWidget_33H_2->setItem(0,2,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[2])));
    ui->tableWidget_33H_2->setItem(0,3,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[3])));
    ui->tableWidget_33H_2->setItem(0,4,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[4])));
    ui->tableWidget_33H_2->setItem(0,5,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[5])));
    ui->tableWidget_33H_2->setItem(0,6,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[6])));
    ui->tableWidget_33H_2->setItem(0,7,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[7])));
    ui->tableWidget_33H_2->setItem(0,8,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[8])));
    ui->tableWidget_33H_2->setItem(0,9,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[9])));
    ui->tableWidget_33H_2->setItem(0,10,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[10])));
    ui->tableWidget_33H_2->setItem(0,11,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[11])));
    ui->tableWidget_33H_2->setItem(0,12,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[12])));
    ui->tableWidget_33H_2->setItem(0,13,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[13])));
    ui->tableWidget_33H_2->setItem(0,14,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[14])));
    ui->tableWidget_33H_2->setItem(0,15,new QTableWidgetItem(QString("%1").arg(p33H->u2RealData[15])));

    ui->tableWidget_33H_1->resizeColumnsToContents();
    ui->tableWidget_33H_1->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_33H_1->show();
    ui->tableWidget_33H_2->resizeColumnsToContents();
    ui->tableWidget_33H_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_33H_2->show();

}

short int CRecvDialog::GetComplement(short int a)  //求补码
{
    if(a & 0x8000)
    {
        a = -(0xFFFF - a + 1);
    }
    return a;
}


void CRecvDialog::clear_33H()
{
    ui->tableWidget_33H_1->clearContents();
    ui->tableWidget_33H_2->clearContents();
    ui->label_AcqTime->clear();
    ui->label_17ADC->clear();
    ui->label_18ADC->clear();
}
QByteArray CRecvDialog::MakeSave(const T33H *p33H)
{
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("33H:%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11 %12 %13 %14 %15 %16 %17 %18 %19 \r\n  %20 %21 %22 %23 %24 %25 %26 %27 %28 %29 %30 %31 %32 %33 %34 %35\r\n")
                    .arg(p33H->u2Time)
                    .arg(p33H->u2OriginData[0])
                    .arg(p33H->u2OriginData[1])
                    .arg(p33H->u2OriginData[2])
                    .arg(p33H->u2OriginData[3])
                    .arg(p33H->u2OriginData[4])
                    .arg(p33H->u2OriginData[5])
                    .arg(p33H->u2OriginData[6])
                    .arg(p33H->u2OriginData[7])
                    .arg(p33H->u2OriginData[8])
                    .arg(p33H->u2OriginData[9])
                    .arg(p33H->u2OriginData[10])
                    .arg(p33H->u2OriginData[11])
                    .arg(p33H->u2OriginData[12])
                    .arg(p33H->u2OriginData[13])
                    .arg(p33H->u2OriginData[14])
                    .arg(p33H->u2OriginData[15])
                    .arg(p33H->u2OriginData[16])
                    .arg(p33H->u2OriginData[17])
            .arg(p33H->u2RealData[0])
            .arg(p33H->u2RealData[1])
            .arg(p33H->u2RealData[2])
            .arg(p33H->u2RealData[3])
            .arg(p33H->u2RealData[4])
            .arg(p33H->u2RealData[5])
            .arg(p33H->u2RealData[6])
            .arg(p33H->u2RealData[7])
            .arg(p33H->u2RealData[8])
            .arg(p33H->u2RealData[9])
            .arg(p33H->u2RealData[10])
            .arg(p33H->u2RealData[11])
            .arg(p33H->u2RealData[12])
            .arg(p33H->u2RealData[13])
            .arg(p33H->u2RealData[14])
            .arg(p33H->u2RealData[15])
            );
    return BtAryMsg;

}
