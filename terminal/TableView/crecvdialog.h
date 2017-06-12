#ifndef CRECVDIALOG_H
#define CRECVDIALOG_H

#include <QDialog>
#include "bin.h"
#include <QTableWidget>
#include <QString>
#include <QByteArray>

namespace Ui {
class CRecvDialog;
}

class CRecvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CRecvDialog(QWidget *parent = 0);
    ~CRecvDialog();

private:
    Ui::CRecvDialog *ui;
public:
    void Update33H(const T33H *p33H);
    void clear_33H();
    QByteArray MakeSave(const T33H *p33H);
    short int GetComplement(short int a);
};

#endif // CRECVDIALOG_H
