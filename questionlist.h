#ifndef QUESTIONLIST_H
#define QUESTIONLIST_H

#include <QVector>
#include "question.h"


class questionlist
{
public:
    questionlist();
    questionlist(Question q);
    QVector<Question> m_questionlist;

};

#endif // QUESTIONLIST_H
