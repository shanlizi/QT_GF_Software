#ifndef CRECV34HDIALOG_H
#define CRECV34HDIALOG_H

#include <QDialog>
#include "bin.h"
#include <QTableWidget>
#include <QString>
#include <QByteArray>

namespace Ui {
class CRecv34HDialog;
}

class CRecv34HDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRecv34HDialog(QWidget *parent = 0);
    ~CRecv34HDialog();

private:
    Ui::CRecv34HDialog *ui;
public:
    void Update34H(const T34H *p34H);
    void clear_34H();
    QByteArray MakeSave(const T34H *p34H);
};

#endif // CRECV34HDIALOG_H
