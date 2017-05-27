#ifndef CRECV35HDIALOG_H
#define CRECV35HDIALOG_H

#include <QDialog>

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
};

#endif // CRECV35HDIALOG_H
