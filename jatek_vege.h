#ifndef JATEK_VEGE_H
#define JATEK_VEGE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class jatek_vege;
}

class jatek_vege : public QDialog
{
    Q_OBJECT

public:
    explicit jatek_vege(QWidget *parent = nullptr);
    ~jatek_vege();
    void setEredmeny(QString jatekos, QString pontszam, QString mennyibol);

private slots:
    void on_jatekvege_ok_clicked();

private:
    Ui::jatek_vege *ui;
    MainWindow *mainwindow;
};

#endif // JATEK_VEGE_H
