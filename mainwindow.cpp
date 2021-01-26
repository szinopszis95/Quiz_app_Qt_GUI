#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newquestion.h"
#include "info.h"
#include "jatek_vege.h"
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(startCountdown()));
    timer->start(1000);

    ui->stackedWidget->setCurrentIndex(0);

    mainFileDirectory = QDir("Kerdesek");

    if (!mainFileDirectory.exists()) {
        QDir().mkdir("Kerdesek");
    }

    refreshQuiz("");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addQuestion(Question question)
{
    ui->questionlist->addItem(question.q);
}

void MainWindow::editQuestion(Question question)
{
    ui->questionlist->insertItem(ui->questionlist->currentRow(),question.q);
    ui->questionlist->takeItem(ui->questionlist->currentRow());

    int index = findQ(question.q);
    q_list.m_questionlist[index].setAll(question);

    ui->questionlist->setCurrentRow(ui->questionlist->currentRow()-1);
}

void MainWindow::deleteQuestion()
{
    if(ui->questionlist->count() > 1){
        q_list.m_questionlist.remove(ui->questionlist->currentRow());
    }
    else
        q_list.m_questionlist.clear();
}

void MainWindow::updateQlist(Question question)
{
    q_list.m_questionlist.append(question);
}

int MainWindow::findQ(QString question_name)
{
    for (int i = 0; i < q_list.m_questionlist.size(); i++){
        if(question_name == q_list.m_questionlist[i].q){
             return i;
        }
    }
    return -1;
}


void MainWindow::refreshQuiz(QString filename)
{
    if(ui->label_4->text() == ""){
    filename = "neurobiosz_i.qvz";
    }

    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::critical(this, "Hiba", "A file nem megfelelő");
    }


    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString line, q_name, A, B, C, D, Ans;
    QFileInfo info(file.fileName());

    stream.readLineInto(&line);
    QStringList list = line.split(":");
    ui->label_4->setText(list[1]);

    while(stream.readLineInto(&line)) {
        QStringList list = line.split(":");

        if(list[0] == "Q"){
            q_name = list[1];
        }
        if(list[0] == "A"){
            A = list[1];
        }
        if(list[0] == "B"){
            B = list[1];
        }
        if(list[0] == "C"){
            C = list[1];
        }
        if(list[0] == "D"){
            D = list[1];
        }
        if(list[0] == "Ans"){
            list[1].chop(1);
            Ans = list[1];
            Question egykerdes(q_name, A, B, C, D, Ans);
            updateQlist(egykerdes);
        }
    }

    for(auto a:q_list.m_questionlist){
        addQuestion(a);
    }

    ui->stackedWidget->setCurrentIndex(0);
    file.close();
}

void MainWindow::startQuiz()
{
    resetCountdown();
    startCountdown();
    if(ui->questionlist->count() == 0){
        QMessageBox::critical(this, "Hiba", "Nincs kérdés betöltve");
        return;
    }
    std::random_shuffle(q_list.m_questionlist.begin(), q_list.m_questionlist.end());
    ui->stackedWidget->setCurrentIndex(1);
    ui->kerdessorozat_neve->setText(ui->kerdessor_neve->text());
    ui->kerdes_szama->setText(QString::number(1));
    ui->kerdes_size->setText("/  " + QString::number(q_list.m_questionlist.size()));
    ui->aktualis_kerdes->setText(q_list.m_questionlist[0].q);
    QList<QString> valaszok = {q_list.m_questionlist[0].A, q_list.m_questionlist[0].B, q_list.m_questionlist[0].C, q_list.m_questionlist[0].D };
    std::random_shuffle(valaszok.begin(), valaszok.end());
    ui->A_valasz->setText(valaszok[0]);
    ui->B_valasz->setText(valaszok[1]);
    ui->C_valasz->setText(valaszok[2]);
    ui->D_valasz->setText(valaszok[3]);
    ui->aktualis_pontszam->setText("0");
}


void MainWindow::on_uj_kerdes_clicked()
{
    newquestion *newItem
            = new newquestion(this);
    newItem->show();

}

void MainWindow::on_kerdes_szerkesztese_clicked()
{
    if(ui->questionlist->count() == 0){
        QMessageBox::critical(this, "Hiba", "Nincs mit szerkeszteni");
        return;
    }
    if(ui->questionlist->currentRow() == -1)
    {
        QMessageBox::critical(this, "Hiba", "Nincs kérdés kijelölve");
         return;
        }
    ui->kerdessor_neve->setText(ui->label_4->text());
    newquestion *newItem
            = new newquestion(this);
    newItem->show();

    QString currentitem = ui->questionlist->currentItem()->text();
    int index = findQ(currentitem);

    newItem->setData(q_list.m_questionlist[index]);
}

void MainWindow::on_kerdes_torlese_clicked()
{
    if(ui->questionlist->count() == 0){
        QMessageBox::critical(this, "Hiba", "Nincs mit törölni");
        return;
    }
    if(ui->questionlist->currentRow() == -1)
    {
        QMessageBox::critical(this, "Hiba", "Nincs kérdés kijelölve");
         return;
        }
    delete ui->questionlist->takeItem(ui->questionlist->currentRow());
    deleteQuestion();
}

void MainWindow::on_kovetkezo_kerdes_clicked()
{
    resetCountdown();
    startCountdown();
    int jelenlegi = ui->aktualis_pontszam->text().toInt();
    int hanyadik = ui->kerdes_szama->text().toInt()-1;
    QString temp;
    QList<QString> valaszok = {q_list.m_questionlist[hanyadik].A, q_list.m_questionlist[hanyadik].B, q_list.m_questionlist[hanyadik].C, q_list.m_questionlist[hanyadik].D, q_list.m_questionlist[hanyadik].Ans};
    QString jovalasz;
    if (valaszok[4] == "A"){
        jovalasz = valaszok[0];
    }
    if (valaszok[4] == "B"){
        jovalasz = valaszok[1];
    }
    if (valaszok[4] == "C"){
        jovalasz = valaszok[2];
    }
    if (valaszok[4] == "D"){
        jovalasz = valaszok[3];
    }
    if(ui->A_valasz->isChecked()){
        ui->A_valasz->setAutoExclusive(false);
        ui->A_valasz->setChecked(false);
        ui->A_valasz->setAutoExclusive(true);
        temp = ui->A_valasz->text();
    }
    if(ui->B_valasz->isChecked()){
        ui->B_valasz->setAutoExclusive(false);
        ui->B_valasz->setChecked(false);
        ui->B_valasz->setAutoExclusive(true);
        temp = ui->B_valasz->text();
    }
    if(ui->C_valasz->isChecked()){
        ui->C_valasz->setAutoExclusive(false);
        ui->C_valasz->setChecked(false);
        ui->C_valasz->setAutoExclusive(true);
        temp = ui->C_valasz->text();
    }
    if(ui->D_valasz->isChecked()){
        ui->D_valasz->setAutoExclusive(false);
        ui->D_valasz->setChecked(false);
        ui->D_valasz->setAutoExclusive(true);
        temp = ui->D_valasz->text();
    }

    if(jovalasz == temp){
        ui->aktualis_pontszam->setText(QString::number(jelenlegi+1));
    }

    if(hanyadik == q_list.m_questionlist.size()-1){
        jatek_vege *egyjatek = new jatek_vege(this);
        egyjatek->show();
        egyjatek->setEredmeny(ui->jatekos_neve->text(), ui->aktualis_pontszam->text(), QString::number(q_list.m_questionlist.size()));
        ui->label_4->setText(ui->kerdessor_neve->text());
        ui->stackedWidget->setCurrentIndex(0);
        return;
    }

    else
    ui->kerdes_szama->setText(QString::number(hanyadik+2));
    ui->aktualis_kerdes->setText(q_list.m_questionlist[hanyadik+1].q);
    QList<QString> valaszok_uj = {q_list.m_questionlist[hanyadik+1].A, q_list.m_questionlist[hanyadik+1].B, q_list.m_questionlist[hanyadik+1].C, q_list.m_questionlist[hanyadik+1].D};
    std::random_shuffle(valaszok_uj.begin(), valaszok_uj.end());
    ui->A_valasz->setText(valaszok_uj[0]);
    ui->B_valasz->setText(valaszok_uj[1]);
    ui->C_valasz->setText(valaszok_uj[2]);
    ui->D_valasz->setText(valaszok_uj[3]);


}

void MainWindow::on_action_j_j_t_k_triggered()
{
    startQuiz();
}

void MainWindow::on_jatek_inditasa_clicked()
{
    startQuiz();
}

void MainWindow::on_actionMegl_v_szerkeszt_se_triggered()
{
    ui->kerdessor_neve->setText(ui->label_4->text());
    if(ui->questionlist->count() == 0){
        for(auto a:q_list.m_questionlist){
            addQuestion(a);
        }
    }
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionJ_t_k_befejez_se_triggered()
{
    if(ui->stackedWidget->currentIndex() != 1){
        QMessageBox::critical(this, "Hiba", "Nem vagy játékban!");
         return;
        }

    jatek_vege *egyjatek = new jatek_vege(this);
    egyjatek->show();
    egyjatek->setEredmeny(ui->jatekos_neve->text(), ui->aktualis_pontszam->text(), QString::number(q_list.m_questionlist.size()));
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_action_j_k_rd_ssor_triggered()
{
    q_list.m_questionlist.clear();
    ui->kerdessor_neve->clear();
    ui->questionlist->clear();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_actionK_rd_ssor_kiv_laszt_sa_triggered()
{
    {
        QString filter = "QVZ files (*.qvz) ;; All file (*.*)";
        QString filename = QFileDialog::getOpenFileName(this, "Válaszd ki a kérdéssort!", "C:/", filter);
        if (filename != "") {
            ui->questionlist->clear();
            q_list.m_questionlist.clear();
            refreshQuiz(filename);
        }
    }
}

void MainWindow::on_actionKil_p_s_triggered()
{
    QApplication::quit();
}


void MainWindow::on_mentes_clicked()
{
    QString name = ui->kerdessor_neve->text();
    name = name.toLower();
    name.replace(" ", "_");

    QFile file(mainFileDirectory.absolutePath() + "/" + name + ".qvz");

    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::critical(this, "Hiba", "A fájlt nem lehet megnyitni.");
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream << "Name:" << ui->kerdessor_neve->text() << "\n";

    for(auto a : q_list.m_questionlist){
        stream << "Q:" << a.q << "\n";
        stream << "A:" << a.A << "\n";
        stream << "B:" << a.B << "\n";
        stream << "C:" << a.C << "\n";
        stream << "D:" << a.D << "\n";
        stream << "Ans:" << a.Ans << ";" << "\n";
    }

    file.flush();
    file.close();
    QMessageBox::information(this, "Siker", "Sikeresen mentve!");

}


void MainWindow::on_actionQuiz_info_triggered()
{
    Info *newinfo = new Info(this);
    newinfo->show();
}

void MainWindow::startCountdown()
{
    ui->hatralevo_ido->setText(QString::number(x));
    x -= 1;
    if(x == 0){
        on_kovetkezo_kerdes_clicked();
    }
}

void MainWindow::resetCountdown()
{
    x = 15;
}
