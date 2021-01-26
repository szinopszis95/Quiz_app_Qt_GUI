#include "q_list.h"

q_list::q_list(QObject *parent) : QObject(parent)
{

}

q_list::QuestionList q_list::questions() const
{
    return m_questions;
}

q_entry *q_list::createEntry()
{
    auto result = new q_entry(this);
    if ( result != nullptr){
        m_questions.append(result);
        emit entryAdded(result);
    }
    return result;
}

bool q_list::deleteEntry(q_entry *entry)
{
    if (m_questions.contains(entry)){
        emit entryRemoved(entry);
        m_questions.removeOne(entry);
        delete entry;
        return true;
    }
    return false;
}
