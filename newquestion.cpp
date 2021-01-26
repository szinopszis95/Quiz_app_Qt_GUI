#include "newquestion.h"
#include "question.h"
#include <QMessageBox>

newquestion::newquestion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newquestion)
{
    ui->setupUi(this);
    mainwindow = dynamic_cast<MainWindow*>(parent);
}

newquestion::~newquestion()
{
    delete ui;
}

void newquestion::on_Ok_clicked()
{
    Question editq(ui->kerdes->text(), ui->A_valasz->text(), ui->B_valasz->text(), ui->C_valasz->text(), ui->D_valasz->text(), ui->Ans->currentText());

    if(mainwindow->findQ(editq.q) != -1){
    mainwindow->editQuestion(editq);
    }

    else {
        mainwindow->addQuestion(editq);
        mainwindow->updateQlist(editq);
    }


    QDialog::accept();
}

void newquestion::setData(Question q)
{
    int index = -1;
    ui->kerdes->setText(q.q);
    ui->A_valasz->setText(q.A);
    ui->B_valasz->setText(q.B);
    ui->C_valasz->setText(q.C);
    ui->D_valasz->setText(q.D);
    if (q.Ans == "A"){
        index = 0;
    }
    if (q.Ans == "B"){
        index = 1;
    }
    if (q.Ans == "C"){
        index = 2;
    }
    if (q.Ans == "D"){
        index = 3;
    }
    ui->Ans->setCurrentIndex(index);
}

void newquestion::on_Cancel_clicked()
{
    QDialog::reject();
}
