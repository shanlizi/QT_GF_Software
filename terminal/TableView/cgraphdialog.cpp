#include "cgraphdialog.h"
#include "ui_cgraphdialog.h"

CGraphDialog::CGraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGraphDialog)
{
    ui->setupUi(this);
    bFlagIsFirst = true;
    readSettings();
    ui->radioButton_Time->setChecked(true);
    /*
    ui->checkBox1->setChecked(true);
    ui->checkBox2->setChecked(true);
    ui->checkBox3->setChecked(true);
    ui->checkBox4->setChecked(true);
    ui->checkBox5->setChecked(true);
    ui->checkBox6->setChecked(true);
    ui->checkBox7->setChecked(true);
    ui->checkBox8->setChecked(true);
    ui->checkBox9->setChecked(true);
    ui->checkBox10->setChecked(true);
    ui->checkBox11->setChecked(true);
    ui->checkBox12->setChecked(true);
    ui->checkBox13->setChecked(true);
    ui->checkBox14->setChecked(true);
    ui->checkBox15->setChecked(true);
    ui->checkBox16->setChecked(true);
    */

}

CGraphDialog::~CGraphDialog()
{
    saveSettings();
    delete ui;
}

/*
void CGraphDialog::InitGraph()
{
    ui->widget_Graph->setInteractions(QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iRangeZoom | QCP::iRangeDrag);
    ui->widget_Graph->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->widget_Graph->legend->setFont(legendFont);
    ui->widget_Graph->legend->setSelectedFont(legendFont);
    ui->widget_Graph->legend->setSelectableParts(QCPLegend::spItems);

    QVector<double> x(301), y(301); // initialize with entries 0..100
    for (int i=0; i<301; ++i)
    {
      x[i] = i/20.0 - 1; // x goes from -1 to 1
      y[i] = sin(x[i]); // let's plot a quadratic function

    }

    ui->widget_Graph->addGraph();

    ui->widget_Graph->graph(0)->setPen(QPen(Qt::blue));
    ui->widget_Graph->graph(0)->setAntialiasedFill(false);
    ui->widget_Graph->graph(0)->setName("HDOP");

    ui->widget_Graph->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    //ui->widget_Graph->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->widget_Graph->xAxis->setDateTimeFormat("ss");
    ui->widget_Graph->xAxis->setAutoTickStep(false);
    ui->widget_Graph->xAxis->setTickStep(1);


    ui->widget_Graph->graph(0)->setData(x, y);
    // 为坐标轴添加标签
    ui->widget_Graph->xAxis->setLabel("x");
    ui->widget_Graph->yAxis->setLabel("y");
    // 设置坐标轴的范围，以看到所有数据
    ui->widget_Graph->xAxis->setRange(-2, 15);
    //ui->widget_Graph->xAxis->setRange(key+1.0, 60, Qt::AlignRight);
    qSort(y.begin(), y.end());
    /*
    if(y.last() < 4)
        ui->widget_Graph->yAxis->setRange(-5,5);
    else if(y.last() < 8)
        ui->widget_Graph->yAxis->setRange(-10,10);
    else if(y.last() < 16)
        ui->widget_Graph->yAxis->setRange(-20,20);
    else
        ui->widget_Graph->yAxis->setRange(-100,100);

    ui->widget_Graph->yAxis->setRange(-1.5,y.last()+1.0);
    // 添加数据曲线（一个图像可以有多个数据曲线）;
    //ui->widget_Graph->graph(0)->removeDataBefore(7);
    ui->widget_Graph->replot(); // 重画图像
}
*/

//unsigned short x, unsigned short y
void CGraphDialog::InitGraph()
{
    ui->widget_Graph->setInteractions(QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iRangeZoom | QCP::iRangeDrag);
    ui->widget_Graph->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->widget_Graph->legend->setFont(legendFont);
    ui->widget_Graph->legend->setSelectedFont(legendFont);
    ui->widget_Graph->legend->setSelectableParts(QCPLegend::spItems);


    ui->widget_Graph->addGraph();

    ui->widget_Graph->graph(0)->setPen(QPen(Qt::blue));
    ui->widget_Graph->graph(0)->setAntialiasedFill(false);
    ui->widget_Graph->graph(0)->setName("HDOP");

    ui->widget_Graph->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    //ui->widget_Graph->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->widget_Graph->xAxis->setDateTimeFormat("ss");
    ui->widget_Graph->xAxis->setAutoTickStep(false);
    ui->widget_Graph->xAxis->setTickStep(1);


    // 为坐标轴添加标签
    ui->widget_Graph->xAxis->setLabel("x");
    ui->widget_Graph->yAxis->setLabel("y");
    // 设置坐标轴的范围，以看到所有数据
    ui->widget_Graph->xAxis->setRange(-2, 15);
    //ui->widget_Graph->xAxis->setRange(key+1.0, 60, Qt::AlignRight);

   /* qSort(y.begin(), y.end());
    if(y.last() < 4)
        ui->widget_Graph->yAxis->setRange(-5,5);
    else if(y.last() < 8)
        ui->widget_Graph->yAxis->setRange(-10,10);
    else if(y.last() < 16)
        ui->widget_Graph->yAxis->setRange(-20,20);
    else
        ui->widget_Graph->yAxis->setRange(-100,100);
        */
    ui->widget_Graph->yAxis->setRange(-2, 2.0);
    // 添加数据曲线（一个图像可以有多个数据曲线）;
    //ui->widget_Graph->graph(0)->removeDataBefore(7);
    //ui->widget_Graph->replot(); // 重画图像
}

void CGraphDialog::DrawGraph(QVector<double> xx, QVector<double> yy[16], QVector<double> xx_DAC[16])
{
    QVector<double> x(xx);
    QVector<double> y[16];
    QVector<double> x_DAC[16];
    double y_minlength = 0.0;
    double y_maxlength = 0.0;
    double xDAC_minlength = 0.0;
    double xDAC_maxlength = 0.0;


    for(int j=0;j<16;j++)
    {
        y[j] = yy[j];
    }


    for(int j=0;j<16;j++)
    {
        x_DAC[j] = xx_DAC[j];
    }



    ui->widget_Graph->replot(); // 重画图像
    ui->widget_Graph->clearGraphs();

    ui->widget_Graph->setInteractions(QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iRangeZoom | QCP::iRangeDrag);
    ui->widget_Graph->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->widget_Graph->legend->setFont(legendFont);
    ui->widget_Graph->legend->setSelectedFont(legendFont);
    ui->widget_Graph->legend->setSelectableParts(QCPLegend::spItems);

    /*
    QVector<double> x(301), y(301); // initialize with entries 0..100
    for (int i=0; i<301; ++i)
    {
      x[i] = i/20.0 - 1; // x goes from -1 to 1
      y[i] = sin(x[i]); // let's plot a quadratic function

    }
    */

    QString str[16];
    if(ui->radioButton_Time->isChecked())
    {
        str[0] = "ADC_1";
        str[1] = "ADC_2";
        str[2] = "ADC_3";
        str[3] = "ADC_4";
        str[4] = "ADC_5";
        str[5] = "ADC_6";
        str[6] = "ADC_7";
        str[7] = "ADC_8";
        str[8] = "ADC_9";
        str[9] = "ADC_10";
        str[10] = "ADC_11";
        str[11] = "ADC_12";
        str[12] = "ADC_13";
        str[13] = "ADC_14";
        str[14] = "ADC_15";
        str[15] = "ADC_16";
    }
    else
    {
        str[0] = "DAC_1";
        str[1] = "DAC_2";
        str[2] = "DAC_3";
        str[3] = "DAC_4";
        str[4] = "DAC_5";
        str[5] = "DAC_6";
        str[6] = "DAC_7";
        str[7] = "DAC_8";
        str[8] = "DAC_9";
        str[9] = "DAC_10";
        str[10] = "DAC_11";
        str[11] = "DAC_12";
        str[12] = "DAC_13";
        str[13] = "DAC_14";
        str[14] = "DAC_15";
        str[15] = "DAC_16";
    }
    QPen pen[4] = {QPen(Qt::blue),QPen(Qt::green),QPen(Qt::red),QPen(Qt::yellow)};


    if(ui->radioButton_Time->isChecked())
    {
        for(int j=0;j<16;j++)
        {
            ui->widget_Graph->addGraph();
            ui->widget_Graph->graph(j)->setPen(pen[j%4]);
            ui->widget_Graph->graph(j)->setAntialiasedFill(false);
            ui->widget_Graph->graph(j)->setName(str[j]);
            ui->widget_Graph->graph(j)->setData(x, y[j]);
        }
    }
    else
    {
        for(int j=0;j<16;j++)
        {
            ui->widget_Graph->addGraph();
            ui->widget_Graph->graph(j)->setPen(pen[j%4]);
            ui->widget_Graph->graph(j)->setAntialiasedFill(false);
            ui->widget_Graph->graph(j)->setName(str[j]);
            ui->widget_Graph->graph(j)->setData(x_DAC[j], y[j]);
        }
    }


    if(ui->radioButton_Time->isChecked())
    {
        ui->widget_Graph->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        //ui->widget_Graph->xAxis->setDateTimeFormat("hh:mm:ss");
        ui->widget_Graph->xAxis->setDateTimeFormat("ss");
        ui->widget_Graph->xAxis->setAutoTickStep(false);
        ui->widget_Graph->xAxis->setTickStep(1);

        ui->widget_Graph->xAxis->setLabel("x_(time/s)");
    }
    else
    {
        ui->widget_Graph->xAxis->setTickLabelType(QCPAxis::ltNumber);
        ui->widget_Graph->xAxis->setAutoTickStep(true);
        ui->widget_Graph->xAxis->setLabel("x_DAC(mV))");
    }





    // 为坐标轴添加标签
    ui->widget_Graph->yAxis->setLabel("y_ADC(nA)");
    // 设置坐标轴的范围，以看到所有数据

    qSort(x.begin(), x.end());
    if(x.last() < 20)
        ui->widget_Graph->xAxis->setTickStep(1);
    else if(x.last() >= 20 && x.last() < 60)
        ui->widget_Graph->xAxis->setTickStep(5);
    else
        ui->widget_Graph->xAxis->setTickStep(10);

    //ui->widget_Graph->xAxis->setRange(0, x.last()*1.2+5);
    //ui->widget_Graph->xAxis->setRange(key+1.0, 60, Qt::AlignRight);


    //DAC排序算出显示范围
    for(int j=0;j<16;j++)
    {
        qSort(y[j].begin(), y[j].end());
        y_max.push_back(y[j].last());
        y_min.push_back(y[j].first());

        qSort(x_DAC[j].begin(), x_DAC[j].end());
        xDAC_max.push_back(x_DAC[j].last());
        xDAC_min.push_back(x_DAC[j].first());
    }
    qSort(y_max.begin(), y_max.end());
    qSort(y_min.begin(), y_min.end());

    qSort(xDAC_max.begin(), xDAC_max.end());
    qSort(xDAC_min.begin(), xDAC_min.end());


    /*
    if(y.last() < 4)
        ui->widget_Graph->yAxis->setRange(-5,5);
    else if(y.last() < 8)
        ui->widget_Graph->yAxis->setRange(-10,10);
    else if(y.last() < 16)
        ui->widget_Graph->yAxis->setRange(-20,20);
    else
        ui->widget_Graph->yAxis->setRange(-100,100);
    */

    y_minlength = y_min.first()*0.9;
    y_maxlength = y_max.last()*1.1;
    //xDAC_minlength
    xDAC_minlength = xDAC_min.first()*0.9;
    xDAC_maxlength = xDAC_max.last()*1.1;
    if(y_min.first() < 0)
    {
        y_minlength = y_min.first()*1.1;
    }
    if(y_max.last() < 0)
    {
        y_maxlength = y_max.last()*0.9;
    }

    if(xDAC_min.first() < 0)
    {
        xDAC_minlength = xDAC_min.first()*1.1;
    }
    if(xDAC_max.last() < 0)
    {
        xDAC_maxlength = xDAC_max.last()*0.9;
    }

    if(ui->radioButton_Time->isChecked())
    {
        ui->widget_Graph->xAxis->setRange(0, x.last()*1.2+5);
    }
    else
    {
        ui->widget_Graph->xAxis->setRange(xDAC_minlength, xDAC_maxlength);
    }
    ui->widget_Graph->yAxis->setRange(y_minlength, y_maxlength);
    // 添加数据曲线（一个图像可以有多个数据曲线）;
    //ui->widget_Graph->graph(0)->removeDataBefore(7);

    if(!ui->checkBox1->isChecked())
    {
        ui->widget_Graph->graph(0)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox2->isChecked())
    {
        ui->widget_Graph->graph(1)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox3->isChecked())
    {
        ui->widget_Graph->graph(2)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox4->isChecked())
    {
        ui->widget_Graph->graph(3)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox5->isChecked())
    {
        ui->widget_Graph->graph(4)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox6->isChecked())
    {
        ui->widget_Graph->graph(5)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox7->isChecked())
    {
        ui->widget_Graph->graph(6)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox8->isChecked())
    {
        ui->widget_Graph->graph(7)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox9->isChecked())
    {
        ui->widget_Graph->graph(8)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox10->isChecked())
    {
        ui->widget_Graph->graph(9)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox11->isChecked())
    {
        ui->widget_Graph->graph(10)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox12->isChecked())
    {
        ui->widget_Graph->graph(11)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox13->isChecked())
    {
        ui->widget_Graph->graph(12)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox14->isChecked())
    {
        ui->widget_Graph->graph(13)->setPen(QPen(Qt::white));
    }

    if(!ui->checkBox15->isChecked())
    {
        ui->widget_Graph->graph(14)->setPen(QPen(Qt::white));
    }
    if(!ui->checkBox16->isChecked())
    {
        ui->widget_Graph->graph(15)->setPen(QPen(Qt::white));
    }

}

void CGraphDialog::clearGraph()
{
    ui->widget_Graph->clearGraphs();
    ui->widget_Graph->replot();
}

void CGraphDialog::on_checkBoxAll_clicked(bool checked)
{
    ui->checkBox1->setChecked(checked);
    ui->checkBox2->setChecked(checked);
    ui->checkBox3->setChecked(checked);
    ui->checkBox4->setChecked(checked);
    ui->checkBox5->setChecked(checked);
    ui->checkBox6->setChecked(checked);
    ui->checkBox7->setChecked(checked);
    ui->checkBox8->setChecked(checked);
    ui->checkBox9->setChecked(checked);
    ui->checkBox10->setChecked(checked);
    ui->checkBox11->setChecked(checked);
    ui->checkBox12->setChecked(checked);
    ui->checkBox13->setChecked(checked);
    ui->checkBox14->setChecked(checked);
    ui->checkBox15->setChecked(checked);
    ui->checkBox16->setChecked(checked);
}

void CGraphDialog::readSettings()
{
    QSettings settings("GF_Graph");

    ui->checkBox1->setChecked(settings.value(QString("checkBox1").arg(1)).toBool());
    ui->checkBox2->setChecked(settings.value(QString("checkBox2").arg(2)).toBool());
    ui->checkBox3->setChecked(settings.value(QString("checkBox3").arg(3)).toBool());
    ui->checkBox4->setChecked(settings.value(QString("checkBox4").arg(4)).toBool());
    ui->checkBox5->setChecked(settings.value(QString("checkBox5").arg(5)).toBool());
    ui->checkBox6->setChecked(settings.value(QString("checkBox6").arg(6)).toBool());
    ui->checkBox7->setChecked(settings.value(QString("checkBox7").arg(7)).toBool());
    ui->checkBox8->setChecked(settings.value(QString("checkBox8").arg(8)).toBool());
    ui->checkBox9->setChecked(settings.value(QString("checkBox9").arg(9)).toBool());
    ui->checkBox10->setChecked(settings.value(QString("checkBox10").arg(10)).toBool());
    ui->checkBox11->setChecked(settings.value(QString("checkBox11").arg(11)).toBool());
    ui->checkBox12->setChecked(settings.value(QString("checkBox12").arg(12)).toBool());
    ui->checkBox13->setChecked(settings.value(QString("checkBox13").arg(13)).toBool());
    ui->checkBox14->setChecked(settings.value(QString("checkBox14").arg(14)).toBool());
    ui->checkBox15->setChecked(settings.value(QString("checkBox15").arg(15)).toBool());
    ui->checkBox16->setChecked(settings.value(QString("checkBox16").arg(16)).toBool());
}
void CGraphDialog::saveSettings()
{
    QSettings settings("GF_Graph");

    settings.setValue(QString("checkBox1").arg(1),ui->checkBox1->isChecked());
    settings.setValue(QString("checkBox2").arg(2),ui->checkBox2->isChecked());
    settings.setValue(QString("checkBox3").arg(3),ui->checkBox3->isChecked());
    settings.setValue(QString("checkBox4").arg(4),ui->checkBox4->isChecked());
    settings.setValue(QString("checkBox5").arg(5),ui->checkBox5->isChecked());
    settings.setValue(QString("checkBox6").arg(6),ui->checkBox6->isChecked());
    settings.setValue(QString("checkBox7").arg(7),ui->checkBox7->isChecked());
    settings.setValue(QString("checkBox8").arg(8),ui->checkBox8->isChecked());
    settings.setValue(QString("checkBox9").arg(9),ui->checkBox9->isChecked());
    settings.setValue(QString("checkBox10").arg(10),ui->checkBox10->isChecked());
    settings.setValue(QString("checkBox11").arg(11),ui->checkBox11->isChecked());
    settings.setValue(QString("checkBox12").arg(12),ui->checkBox12->isChecked());
    settings.setValue(QString("checkBox13").arg(13),ui->checkBox13->isChecked());
    settings.setValue(QString("checkBox14").arg(14),ui->checkBox14->isChecked());
    settings.setValue(QString("checkBox15").arg(15),ui->checkBox15->isChecked());
    settings.setValue(QString("checkBox16").arg(16),ui->checkBox16->isChecked());
}

