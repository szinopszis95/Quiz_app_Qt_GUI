#include "jatek_vege.h"

jatek_vege::jatek_vege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jatek_vege)
{
    ui->setupUi(this);
    mainwindow = dynamic_cast<MainWindow*>(parent);
}

jatek_vege::~jatek_vege()
{
    delete ui;
}

void jatek_vege::setEredmeny(QString _jatekos, QString _pontszam, QString _mennyibol)
{
   ui->vegso_pontszam->setText(_pontszam + " választ");
   ui->jatekos_nev->setText(_jatekos);
   ui->mennyibol->setText(_mennyibol + " kérdésből eltaláltál");
}

void jatek_vege::on_jatekvege_ok_clicked()
{
    QDialog::accept();
}
