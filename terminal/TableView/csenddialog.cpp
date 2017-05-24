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
    flag_14H = 1;
    this->windowTitleChanged("hi");
}

void CSendDialog::on_pushButton_adjust_15H_clicked()
{
    flag_15H = 1;
    this->windowTitleChanged("hi");
}

void CSendDialog::on_pushButton_version_clicked()
{
    flag_16H = 1;
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

void CSendDialog::Update32H(const T32H *p32H)
{
    ui->label_32H_12H->setText(QString("%1").arg(" "));
    ui->label_32H_14H->setText(QString("%1").arg(" "));
    ui->label_32H_15H->setText(QString("%1").arg(" "));
    QString strFlag;

    if(0 == p32H->i1flag)
    {
        strFlag = "失败";
    }
    else if(1 == p32H->i1flag)
    {
        strFlag = "成功";
    }
    else
    {
        strFlag = "错误";
    }

    switch (p32H->u2ID)
    {
        case 12:
            ui->label_32H_12H->setText(QString("%1").arg(strFlag));
            break;
        case 13:
            break;
        case 14:
            ui->label_32H_14H->setText(QString("%1").arg(strFlag));
            break;
        case 15:
            ui->label_32H_15H->setText(QString("%1").arg(strFlag));
            break;
        default:
            QMessageBox::information(this,"错误","32H帧ID错误，为%d",p32H->u2ID);
            break;
    }
}

void CSendDialog::clear_31H()
{
    ui->label_model->clear();
}
void CSendDialog::clear_32H()
{
    ui->label_32H_12H->clear();
    ui->label_32H_14H->clear();
}
QByteArray CSendDialog::MakeSave(const T31H *p31H)
{
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("31H：%1\r\n")
            .arg(p31H->i1model)
            );
    return BtAryMsg;
}
QByteArray CSendDialog::MakeSave(const T32H *p32H)
{
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("32H：%1 %2\r\n")
            .arg(p32H->u2ID)
            .arg(p32H->i1flag)
            );
    return BtAryMsg;
}

void CSendDialog::Update36H(const T36H *p36H)
{

    /*for(int i=0; i<50; i++)
    {
        QString strdata;
        strdata.append(p36H->i1version[i]);
        ui->textEdit_version->moveCursor(QTextCursor::End);
        ui->textEdit_version->insertPlainText(strdata);
    }*/
    ui->label_version->setText(QString("%1").arg(p36H->i1version));


}

void CSendDialog::clear_36H()
{
    ui->label_version->clear();
}

QByteArray CSendDialog::MakeSave(const T36H *p36H)
{

}






