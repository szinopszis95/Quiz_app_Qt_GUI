#ifndef Q_LIST_CONTROL_H
#define Q_LIST_CONTROL_H

#include "q_list.h"

#include <QObject>

class q_list_control : public QObject
{
    Q_OBJECT
public:
    explicit q_list_control(q_list *qlist,QObject *parent = nullptr);

    q_entry *createEntry();
    bool deleteEntry(q_entry *entry);

signals:

public slots:

private:

    q_list *m_qlist;
};

#endif // Q_LIST_CONTROL_H
