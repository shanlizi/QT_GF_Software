#ifndef CSENDDIALOG_H
#define CSENDDIALOG_H

#include <QDialog>
#include "bin.h"
#include <QTableWidget>
#include <QString>
#include <QByteArray>

namespace Ui {
class CSendDialog;
}

class CSendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSendDialog(QWidget *parent = 0);
    ~CSendDialog();

private slots:
    void on_pushButton_model_clicked();

    void on_pushButton_setmodel_clicked();

    void on_pushButton_14H_set_clicked();

private:
    Ui::CSendDialog *ui;

public:
    int flag_11H = 0;
    int flag_12H = 0;
    int flag_13H = 0;
    int flag_14H = 0;

public:
    void Update31H(const T31H *p31H);
    void clear_31H();
    QByteArray MakeSave(const T31H *p31H);


};

#endif // CSENDDIALOG_H
