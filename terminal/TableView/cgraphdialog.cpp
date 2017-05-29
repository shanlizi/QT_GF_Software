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
