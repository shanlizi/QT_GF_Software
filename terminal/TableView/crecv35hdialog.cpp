#include "crecv35hdialog.h"
#include "ui_crecv35hdialog.h"

CRecv35HDialog::CRecv35HDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRecv35HDialog)
{
    ui->setupUi(this);
}

CRecv35HDialog::~CRecv35HDialog()
{
    delete ui;
}
