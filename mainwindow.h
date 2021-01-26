#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "question.h"
#include "questionlist.h"
#include <QMainWindow>
#include <QTimer>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addQuestion(Question question);
    void editQuestion(Question question);
    void deleteQuestion();
    void updateQlist(Question question);

    int findQ(QString question_name);

private slots:
    void on_uj_kerdes_clicked();

    void on_kerdes_szerkesztese_clicked();

    void on_kerdes_torlese_clicked();

    void on_kovetkezo_kerdes_clicked();

    void on_action_j_j_t_k_triggered();

    void on_jatek_inditasa_clicked();

    void on_actionMegl_v_szerkeszt_se_triggered();

    void on_actionJ_t_k_befejez_se_triggered();

    void on_action_j_k_rd_ssor_triggered();

    void on_actionK_rd_ssor_kiv_laszt_sa_triggered();

    void on_actionKil_p_s_triggered();

    void on_mentes_clicked();

    void on_actionQuiz_info_triggered();

    void startCountdown();

    void resetCountdown();

private:
    Ui::MainWindow *ui;
    QDir mainFileDirectory;
    questionlist q_list;
    QTimer *timer;
    int x = 15;
    void refreshQuiz(QString filename);
    void startQuiz();
    void nextQ();
    void loadQuiz();
};
#endif // MAINWINDOW_H
