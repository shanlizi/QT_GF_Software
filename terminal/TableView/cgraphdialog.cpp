#include "cgraphdialog.h"
#include "ui_cgraphdialog.h"

CGraphDialog::CGraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CGraphDialog)
{
    ui->setupUi(this);
}

CGraphDialog::~CGraphDialog()
{
    delete ui;
}
void CGraphDialog::DrawGraph()
{
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    ui->widget_Graph->addGraph();

    ui->widget_Graph->graph(0)->setData(x, y);
    // 为坐标轴添加标签
    ui->widget_Graph->xAxis->setLabel("x");
    ui->widget_Graph->yAxis->setLabel("y");
    // 设置坐标轴的范围，以看到所有数据
    ui->widget_Graph->xAxis->setRange(-1, 1);
    ui->widget_Graph->yAxis->setRange(0, 1);
    // 添加数据曲线（一个图像可以有多个数据曲线）;
    ui->widget_Graph->replot(); // 重画图像


}
