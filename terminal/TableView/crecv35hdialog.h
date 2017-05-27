#ifndef CRECV35HDIALOG_H
#define CRECV35HDIALOG_H

#include <QDialog>
#include "bin.h"
#include <QTableWidget>
#include <QString>
#include <QByteArray>

namespace Ui {
class CRecv35HDialog;
}

class CRecv35HDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRecv35HDialog(QWidget *parent = 0);
    ~CRecv35HDialog();

private:
    Ui::CRecv35HDialog *ui;
public:
    void Update35H(const T35H *p35H);
    void clear_35H();
    QByteArray MakeSave(const T35H *p35H);
};

#endif // CRECV35HDIALOG_H
