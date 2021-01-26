#ifndef Q_LIST_H
#define Q_LIST_H

#include "q_entry.h"

#include <QObject>
#include <QList>

class q_list : public QObject
{
    Q_OBJECT
public:

    typedef QList<q_entry*> QuestionList;

    explicit q_list(QObject *parent = nullptr);

    QuestionList questions() const;

    q_entry* createEntry();
    bool deleteEntry( q_entry *entry);

signals:

    void entryAdded(q_entry  *entry);
    void entryRemoved(q_entry *entry);

public slots:

private:
    QuestionList m_questions;
};

#endif // Q_LIST_H
