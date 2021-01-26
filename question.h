#ifndef QUESTION_H
#define QUESTION_H
#include <QString>

class Question
{
public:

    QString q;
    QString A;
    QString B;
    QString C;
    QString D;
    QString Ans;

    Question();
    Question(QString _q, QString _A, QString _B, QString _C, QString _D, QString _Ans);

    void setAll(Question question);

};
#endif // QUESTION_H
