#include "info.h"

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;
}

void Info::on_pushButton_clicked()
{
    QDialog::accept();
}
