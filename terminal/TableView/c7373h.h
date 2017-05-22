#ifndef C7373H_H
#define C7373H_H

#include <QDialog>
#include "bin.h"
#include <QTableWidget>
#include <QString>
#include <QByteArray>

namespace Ui {
class C7373H;
}

class C7373H : public QDialog
{
    Q_OBJECT

public:
    explicit C7373H(QWidget *parent = 0);
    ~C7373H();

private:
    Ui::C7373H *ui;
    QTableWidget *m_pTable;
public:
    void Update7373H(const T7373H *p7373H);
    void clear_7373H();
    QByteArray MakeSave(const T7373H *p7373H);
};

#endif // C7373H_H
