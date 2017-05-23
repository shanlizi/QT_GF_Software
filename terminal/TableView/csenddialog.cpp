#include "csenddialog.h"
#include "ui_csenddialog.h"

CSendDialog::CSendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSendDialog)
{
    ui->setupUi(this);
}

CSendDialog::~CSendDialog()
{
    delete ui;
}

void CSendDialog::on_pushButton_model_clicked()
{
    flag_11H = 1;
    this->windowTitleChanged("hi");
}

void CSendDialog::on_pushButton_setmodel_clicked()
{
   flag_12H = ui->comboBox_model->currentIndex()+1;
   this->windowTitleChanged("hi");
}

void CSendDialog::on_pushButton_14H_set_clicked()
{
    flag_14H = ui->comboBox_14H_LED->currentIndex()*256 + ui->comboBox_14H_channel->currentIndex()+1;
    this->windowTitleChanged("hi");
}

void CSendDialog::Update31H(const T31H *p31H)
{
    ui->label_model->setText(QString("%1").arg(" "));
    QString strFlag;
    if(0 == p31H->i1model)
    {
        strFlag = "停止模式";
    }
    else if(1 == p31H->i1model)
    {
        strFlag = "采集模式";
    }
    else if(2 == p31H->i1model)
    {
        strFlag = "工程模式";
    }
    else if(3 == p31H->i1model)
    {
        strFlag = "校准模式";
    }
    else
    {
        strFlag = "错误";
    }
    ui->label_model->setText(QString("%1").arg(strFlag));

}
void CSendDialog::clear_31H()
{
    ui->label_model->clear();
}
QByteArray CSendDialog::MakeSave(const T31H *p31H)
{
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("31H：%1\r\n")
            .arg(p31H->i1model)
            );
    return BtAryMsg;
}



