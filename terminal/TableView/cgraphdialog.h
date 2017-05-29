#ifndef CGRAPHDIALOG_H
#define CGRAPHDIALOG_H

#include <QDialog>
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
    void DrawGraph();
};

#endif // CGRAPHDIALOG_H
