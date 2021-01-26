#include "question.h"

Question::Question()
{
}
Question::Question(QString _q, QString _A, QString _B, QString _C, QString _D, QString _Ans)
{
    q = _q;
    A = _A;
    B = _B;
    C = _C;
    D = _D;
    Ans = _Ans;
}

void Question::setAll(Question question)
{
    q = question.q;
    A = question.A;
    B = question.B;
    C = question.C;
    D = question.D;
    Ans = question.Ans;
}



