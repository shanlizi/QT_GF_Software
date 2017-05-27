#include "csenddialog.h"
#include "ui_csenddialog.h"


CSendDialog::CSendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CSendDialog)
{
    ui->setupUi(this);
    flag_11H = 0;
    flag_12H = 0;
    flag_13H = 0;
    flag_14H = 0;
    flag_15H = 0;
    flag_16H = 0;
    m_TAcqParam_13H = {0};

    validator1 = new QIntValidator( -2500, 2500, this );
    validator2 = new QIntValidator( -10000, 10000, this );
    validator3 = new QIntValidator( 0, 1, this );

    ui->lineEdit_1_1->setValidator(validator1);
    ui->lineEdit_1_2->setValidator(validator1);
    ui->lineEdit_1_3->setValidator(validator2);
    ui->lineEdit_1_4->setValidator(validator3);

    ui->lineEdit_2_1->setValidator(validator1);
    ui->lineEdit_2_2->setValidator(validator1);
    ui->lineEdit_2_3->setValidator(validator2);
    ui->lineEdit_2_4->setValidator(validator3);

    ui->lineEdit_3_1->setValidator(validator1);
    ui->lineEdit_3_2->setValidator(validator1);
    ui->lineEdit_3_3->setValidator(validator2);
    ui->lineEdit_3_4->setValidator(validator3);

    ui->lineEdit_4_1->setValidator(validator1);
    ui->lineEdit_4_2->setValidator(validator1);
    ui->lineEdit_4_3->setValidator(validator2);
    ui->lineEdit_4_4->setValidator(validator3);

    ui->lineEdit_5_1->setValidator(validator1);
    ui->lineEdit_5_2->setValidator(validator1);
    ui->lineEdit_5_3->setValidator(validator2);
    ui->lineEdit_6_4->setValidator(validator3);

    ui->lineEdit_6_1->setValidator(validator1);
    ui->lineEdit_6_2->setValidator(validator1);
    ui->lineEdit_6_3->setValidator(validator2);
    ui->lineEdit_6_4->setValidator(validator3);

    ui->lineEdit_7_1->setValidator(validator1);
    ui->lineEdit_7_2->setValidator(validator1);
    ui->lineEdit_7_3->setValidator(validator2);
    ui->lineEdit_7_4->setValidator(validator3);

    ui->lineEdit_8_1->setValidator(validator1);
    ui->lineEdit_8_2->setValidator(validator1);
    ui->lineEdit_8_3->setValidator(validator2);
    ui->lineEdit_8_4->setValidator(validator3);

    ui->lineEdit_9_1->setValidator(validator1);
    ui->lineEdit_9_2->setValidator(validator1);
    ui->lineEdit_9_3->setValidator(validator2);
    ui->lineEdit_9_4->setValidator(validator3);

    ui->lineEdit_10_1->setValidator(validator1);
    ui->lineEdit_10_2->setValidator(validator1);
    ui->lineEdit_10_3->setValidator(validator2);
    ui->lineEdit_10_4->setValidator(validator3);

    ui->lineEdit_11_1->setValidator(validator1);
    ui->lineEdit_11_2->setValidator(validator1);
    ui->lineEdit_11_3->setValidator(validator2);
    ui->lineEdit_11_4->setValidator(validator3);

    ui->lineEdit_12_1->setValidator(validator1);
    ui->lineEdit_12_2->setValidator(validator1);
    ui->lineEdit_12_3->setValidator(validator2);
    ui->lineEdit_12_4->setValidator(validator3);

    ui->lineEdit_13_1->setValidator(validator1);
    ui->lineEdit_13_2->setValidator(validator1);
    ui->lineEdit_13_3->setValidator(validator2);
    ui->lineEdit_13_4->setValidator(validator3);

    ui->lineEdit_14_1->setValidator(validator1);
    ui->lineEdit_14_2->setValidator(validator1);
    ui->lineEdit_14_3->setValidator(validator2);
    ui->lineEdit_14_4->setValidator(validator3);

    ui->lineEdit_15_1->setValidator(validator1);
    ui->lineEdit_15_2->setValidator(validator1);
    ui->lineEdit_15_3->setValidator(validator2);
    ui->lineEdit_15_4->setValidator(validator3);

    ui->lineEdit_16_1->setValidator(validator1);
    ui->lineEdit_16_2->setValidator(validator1);
    ui->lineEdit_16_3->setValidator(validator2);
    ui->lineEdit_16_4->setValidator(validator3);


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

void CSendDialog::on_pushButton_AcpSet_13H_clicked()
{
    flag_13H = 1;
    m_TAcqParam_13H = {0};

    m_TAcqParam_13H.i1Model = ui->comboBox_AcpModel_13H->currentIndex();

    m_TAcqParam_13H.mChannel[0].i2OriginV = ui->lineEdit_1_1->text().toInt();
    m_TAcqParam_13H.mChannel[0].i2HighV = ui->lineEdit_1_2->text().toInt();
    m_TAcqParam_13H.mChannel[0].i2Slope = ui->lineEdit_1_3->text().toInt();
    m_TAcqParam_13H.mChannel[0].i1Range = ui->lineEdit_1_4->text().toInt();

    m_TAcqParam_13H.mChannel[1].i2OriginV = ui->lineEdit_2_1->text().toInt();
    m_TAcqParam_13H.mChannel[1].i2HighV = ui->lineEdit_2_2->text().toInt();
    m_TAcqParam_13H.mChannel[1].i2Slope = ui->lineEdit_2_3->text().toInt();
    m_TAcqParam_13H.mChannel[1].i1Range = ui->lineEdit_2_4->text().toInt();

    m_TAcqParam_13H.mChannel[2].i2OriginV = ui->lineEdit_3_1->text().toInt();
    m_TAcqParam_13H.mChannel[2].i2HighV = ui->lineEdit_3_2->text().toInt();
    m_TAcqParam_13H.mChannel[2].i2Slope = ui->lineEdit_3_3->text().toInt();
    m_TAcqParam_13H.mChannel[2].i1Range = ui->lineEdit_3_4->text().toInt();

    m_TAcqParam_13H.mChannel[3].i2OriginV = ui->lineEdit_4_1->text().toInt();
    m_TAcqParam_13H.mChannel[3].i2HighV = ui->lineEdit_4_2->text().toInt();
    m_TAcqParam_13H.mChannel[3].i2Slope = ui->lineEdit_4_3->text().toInt();
    m_TAcqParam_13H.mChannel[3].i1Range = ui->lineEdit_4_4->text().toInt();

    m_TAcqParam_13H.mChannel[4].i2OriginV = ui->lineEdit_5_1->text().toInt();
    m_TAcqParam_13H.mChannel[4].i2HighV = ui->lineEdit_5_2->text().toInt();
    m_TAcqParam_13H.mChannel[4].i2Slope = ui->lineEdit_5_3->text().toInt();
    m_TAcqParam_13H.mChannel[4].i1Range = ui->lineEdit_6_4->text().toInt();

    m_TAcqParam_13H.mChannel[5].i2OriginV = ui->lineEdit_6_1->text().toInt();
    m_TAcqParam_13H.mChannel[5].i2HighV = ui->lineEdit_6_2->text().toInt();
    m_TAcqParam_13H.mChannel[5].i2Slope = ui->lineEdit_6_3->text().toInt();
    m_TAcqParam_13H.mChannel[5].i1Range = ui->lineEdit_6_4->text().toInt();

    m_TAcqParam_13H.mChannel[6].i2OriginV = ui->lineEdit_7_1->text().toInt();
    m_TAcqParam_13H.mChannel[6].i2HighV = ui->lineEdit_7_2->text().toInt();
    m_TAcqParam_13H.mChannel[6].i2Slope = ui->lineEdit_7_3->text().toInt();
    m_TAcqParam_13H.mChannel[6].i1Range = ui->lineEdit_7_4->text().toInt();

    m_TAcqParam_13H.mChannel[7].i2OriginV = ui->lineEdit_8_1->text().toInt();
    m_TAcqParam_13H.mChannel[7].i2HighV = ui->lineEdit_8_2->text().toInt();
    m_TAcqParam_13H.mChannel[7].i2Slope = ui->lineEdit_8_3->text().toInt();
    m_TAcqParam_13H.mChannel[7].i1Range = ui->lineEdit_8_4->text().toInt();

    m_TAcqParam_13H.mChannel[8].i2OriginV = ui->lineEdit_9_1->text().toInt();
    m_TAcqParam_13H.mChannel[8].i2HighV = ui->lineEdit_9_2->text().toInt();
    m_TAcqParam_13H.mChannel[8].i2Slope = ui->lineEdit_9_3->text().toInt();
    m_TAcqParam_13H.mChannel[8].i1Range = ui->lineEdit_9_4->text().toInt();

    m_TAcqParam_13H.mChannel[9].i2OriginV = ui->lineEdit_10_1->text().toInt();
    m_TAcqParam_13H.mChannel[9].i2HighV = ui->lineEdit_10_2->text().toInt();
    m_TAcqParam_13H.mChannel[9].i2Slope = ui->lineEdit_10_3->text().toInt();
    m_TAcqParam_13H.mChannel[9].i1Range = ui->lineEdit_10_4->text().toInt();

    m_TAcqParam_13H.mChannel[10].i2OriginV = ui->lineEdit_11_1->text().toInt();
    m_TAcqParam_13H.mChannel[10].i2HighV = ui->lineEdit_11_2->text().toInt();
    m_TAcqParam_13H.mChannel[10].i2Slope = ui->lineEdit_11_3->text().toInt();
    m_TAcqParam_13H.mChannel[10].i1Range = ui->lineEdit_11_4->text().toInt();

    m_TAcqParam_13H.mChannel[11].i2OriginV = ui->lineEdit_12_1->text().toInt();
    m_TAcqParam_13H.mChannel[11].i2HighV = ui->lineEdit_12_2->text().toInt();
    m_TAcqParam_13H.mChannel[11].i2Slope = ui->lineEdit_12_3->text().toInt();
    m_TAcqParam_13H.mChannel[11].i1Range = ui->lineEdit_12_4->text().toInt();

    m_TAcqParam_13H.mChannel[12].i2OriginV = ui->lineEdit_13_1->text().toInt();
    m_TAcqParam_13H.mChannel[12].i2HighV = ui->lineEdit_13_2->text().toInt();
    m_TAcqParam_13H.mChannel[12].i2Slope = ui->lineEdit_13_3->text().toInt();
    m_TAcqParam_13H.mChannel[12].i1Range = ui->lineEdit_13_4->text().toInt();

    m_TAcqParam_13H.mChannel[13].i2OriginV = ui->lineEdit_14_1->text().toInt();
    m_TAcqParam_13H.mChannel[13].i2HighV = ui->lineEdit_14_2->text().toInt();
    m_TAcqParam_13H.mChannel[13].i2Slope = ui->lineEdit_14_3->text().toInt();
    m_TAcqParam_13H.mChannel[13].i1Range = ui->lineEdit_14_4->text().toInt();

    m_TAcqParam_13H.mChannel[14].i2OriginV = ui->lineEdit_15_1->text().toInt();
    m_TAcqParam_13H.mChannel[14].i2HighV = ui->lineEdit_15_2->text().toInt();
    m_TAcqParam_13H.mChannel[14].i2Slope = ui->lineEdit_15_3->text().toInt();
    m_TAcqParam_13H.mChannel[14].i1Range = ui->lineEdit_15_4->text().toInt();

    m_TAcqParam_13H.mChannel[15].i2OriginV = ui->lineEdit_16_1->text().toInt();
    m_TAcqParam_13H.mChannel[15].i2HighV = ui->lineEdit_16_2->text().toInt();
    m_TAcqParam_13H.mChannel[15].i2Slope = ui->lineEdit_16_3->text().toInt();
    m_TAcqParam_13H.mChannel[15].i1Range = ui->lineEdit_16_4->text().toInt();

    this->windowTitleChanged("hi");


}

void CSendDialog::on_pushButton_14H_set_clicked()
{ 
    flag_14H = (ui->comboBox_14H_channel->currentIndex()+1) + (ui->comboBox_14H_LED->currentIndex()<<8);
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
    ui->label_32H_13H->setText(QString("%1").arg(" "));
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
            ui->label_32H_13H->setText(QString("%1").arg(strFlag));
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
    ui->label_32H_13H->clear();
    ui->label_32H_14H->clear();
    ui->label_32H_15H->clear();
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
    ui->label_Type->setText(QString("%1").arg(p36H->i1Type));
    ui->label_version->setText(QString("%1").arg(p36H->i1version));
}

void CSendDialog::clear_36H()
{
    ui->label_Type->clear();
    ui->label_version->clear();
}

QByteArray CSendDialog::MakeSave(const T36H *p36H)
{
    QByteArray BtAryMsg;
    BtAryMsg.append(QString("32H：%1 %2\r\n")
            .arg(p36H->i1Type)
            .arg(p36H->i1version)
            );
    return BtAryMsg;

}







