#include "c7373h.h"
#include "ui_c7373h.h"

C7373H::C7373H(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C7373H)
{
    ui->setupUi(this);
    ui->tableWidget_7373H->horizontalHeader()->show();
    ui->tableWidget_7373H->verticalHeader()->show();
}

C7373H::~C7373H()
{
    delete ui;
}

void C7373H::Update7373H(const T7373H *p7373H)
{
    m_pTable = ui->tableWidget_7373H;
   // m_pTable->clearContents();
    m_pTable->setRowCount(5);
    m_pTable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_pTable->insertRow(0);

    QString strDataFlag,strFreNo,strDiffFlag;
    if(0x5555 == p7373H->u2DataFlag)
        strDataFlag = tr("有效");
    else
        strDataFlag = tr("无效");

    if(0x01 == p7373H->u2FreNo)
        strFreNo = tr("B1");
    else if(0x03 == p7373H->u2FreNo)
        strFreNo = tr("B3");
    else
        strFreNo = tr("无效");

    if(0x5555 == p7373H->u2DiffFlag)
        strDiffFlag = tr("有效");
    else
        strDiffFlag = tr("无效");

    m_pTable->setItem(0,0,new QTableWidgetItem(QString("%1").arg(strDataFlag)));
    m_pTable->setItem(0,1,new QTableWidgetItem(QString("%1").arg(p7373H->u2SVNum)));
    m_pTable->setItem(0,2,new QTableWidgetItem(QString("%1").arg(p7373H->u2Serial)));
    m_pTable->setItem(0,3,new QTableWidgetItem(QString("%1").arg(p7373H->u2SVNo)));
    m_pTable->setItem(0,4,new QTableWidgetItem(QString("%1").arg(strFreNo)));
    m_pTable->setItem(0,5,new QTableWidgetItem(QString("%1").arg(strDiffFlag)));
    m_pTable->setItem(0,6,new QTableWidgetItem(QString("%1").arg(p7373H->u2PRFlag)));
    m_pTable->setItem(0,7,new QTableWidgetItem(QString("%1").arg(p7373H->u2ClockCorrectFlag)));
    m_pTable->setItem(0,8,new QTableWidgetItem(QString("%1").arg((p7373H->i4ClockCorrect)*100)));

    m_pTable->resizeColumnsToContents();
    m_pTable->horizontalHeader()->setStretchLastSection(true);
    m_pTable->show();
}
void C7373H::clear_7373H()
{
    ui->tableWidget_7373H->clearContents();
}
QByteArray C7373H::MakeSave(const T7373H *p7373H)
{
    //QString strMsg;
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("%1 %2 %3 %4 %5 %6 %7 %8 %9\r\n")
            .arg(p7373H->u2DataFlag)
            .arg(p7373H->u2SVNum)
            .arg(p7373H->u2Serial)
            .arg(p7373H->u2SVNo)
            .arg(p7373H->u2FreNo)
            .arg(p7373H->u2DiffFlag)
            .arg(p7373H->u2PRFlag)
            .arg(p7373H->u2ClockCorrectFlag)
            .arg((p7373H->i4ClockCorrect)*100)
            );
    return BtAryMsg;
}
