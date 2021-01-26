#include "q_entry.h"

q_entry::q_entry(QObject *parent) : QObject(parent)
{

}


QString q_entry::getQ() const
{
    return Q;
}

void q_entry::setQ(const QString &value)
{
    if(Q != value){
       Q = value;
       emit QChanged();
    }
}

QString q_entry::getA() const
{
    return A;
}

void q_entry::setA(const QString &value)
{
    if(A != value){
       A = value;
       emit AChanged();
    }
}

QString q_entry::getB() const
{
    return B;
}

void q_entry::setB(const QString &value)
{
    if(B != value){
       B = value;
       emit BChanged();
    }
}

QString q_entry::getC() const
{
    return C;
}

void q_entry::setC(const QString &value)
{
    if(C != value){
       C = value;
       emit CChanged();
    }
}

QString q_entry::getD() const
{
    return D;
}

void q_entry::setD(const QString &value)
{
    if(D != value){
       D = value;
       emit DChanged();
    }
}

QString q_entry::getAns() const
{
    return Ans;
}

void q_entry::setAns(const QString &value)
{
    if(Ans != value){
       Ans = value;
       emit AnsChanged();
    }
}
