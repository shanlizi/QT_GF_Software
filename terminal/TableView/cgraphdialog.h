#ifndef CGRAPHDIALOG_H
#define CGRAPHDIALOG_H

#include <QDialog>
#include <math.h>
#include "qcustomplot.h"

namespace Ui {
class CGraphDialog;
}

class CGraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CGraphDialog(QWidget *parent = 0);
    ~CGraphDialog();

private:
    Ui::CGraphDialog *ui;

public:
    void InitGraph();
    void DrawGraph(QVector<double> xx, QVector<double> yy[16], QVector<double> xx_DAC[16]);
    bool bFlagIsFirst;
    void clearGraph();
    void saveSettings();
    void readSettings();
    QVector<double> y_max;
    QVector<double> y_min;
    QVector<double> xDAC_max;
    QVector<double> xDAC_min;

private slots:
    void on_checkBoxAll_clicked(bool checked);
};

#endif // CGRAPHDIALOG_H
