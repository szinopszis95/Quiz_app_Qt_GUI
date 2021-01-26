#include "q_list_control.h"

q_list_control::q_list_control(
        q_list *qlist, QObject *parent) :
    QObject(parent),
    m_qlist(qlist)
{
    Q_ASSERT(qlist != nullptr);
}

q_entry *q_list_control::createEntry()
{
    auto result = m_qlist->createEntry();

    return result;
}

bool q_list_control::deleteEntry(q_entry *entry)
{
    return m_qlist->deleteEntry(entry);
}
