#ifndef NEWQUESTION_H
#define NEWQUESTION_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class newquestion;
}

class newquestion : public QDialog
{
    Q_OBJECT

public:
    explicit newquestion(QWidget *parent = nullptr);
    ~newquestion();
    void setData(Question q);

private slots:
    void on_Cancel_clicked();

    void on_Ok_clicked();

private:
    Ui::newquestion *ui;
    MainWindow *mainwindow;
};

#endif // NEWQUESTION_H
