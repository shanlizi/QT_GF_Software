#ifndef CSENDDIALOG_H
#define CSENDDIALOG_H

#include <QDialog>
#include "bin.h"
#include <QTableWidget>
#include <QString>
#include <QByteArray>
#include <QMessageBox>

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

    void on_pushButton_adjust_15H_clicked();

    void on_pushButton_version_clicked();

    void on_pushButton_AcpSet_13H_clicked();

private:
    Ui::CSendDialog *ui;

public:
    int flag_11H;
    int flag_12H;
    int flag_13H;
    int flag_14H;
    int flag_15H;
    int flag_16H;
    TAcqParam_13H m_TAcqParam_13H;

public:
    void Update31H(const T31H *p31H);
    void clear_31H();
    QByteArray MakeSave(const T31H *p31H);

    void Update32H(const T32H *p32H);
    void clear_32H();
    QByteArray MakeSave(const T32H *p32H);

    void Update36H(const T36H *p36H);
    void clear_36H();
    QByteArray MakeSave(const T36H *p36H);


};

#endif // CSENDDIALOG_H
