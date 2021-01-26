#ifndef Q_ENTRY_H
#define Q_ENTRY_H

#include <QObject>
#include <QString>

class q_entry : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Q READ getQ WRITE setQ NOTIFY QChanged)
    Q_PROPERTY(QString A READ getA WRITE setA NOTIFY AChanged)
    Q_PROPERTY(QString B READ getB WRITE setB NOTIFY BChanged)
    Q_PROPERTY(QString C READ getC WRITE setC NOTIFY CChanged)
    Q_PROPERTY(QString D READ getD WRITE setD NOTIFY DChanged)
    Q_PROPERTY(QString Ans READ getAns WRITE setAns NOTIFY AnsChanged)

public:
    explicit q_entry(QObject *parent = nullptr);


    QString getQ() const;
    void setQ(const QString &value);

    QString getA() const;
    void setA(const QString &value);

    QString getB() const;
    void setB(const QString &value);

    QString getC() const;
    void setC(const QString &value);

    QString getD() const;
    void setD(const QString &value);

    QString getAns() const;
    void setAns(const QString &value);

signals:
    void QChanged();
    void AChanged();
    void BChanged();
    void CChanged();
    void DChanged();
    void AnsChanged();

public slots:

private:
    QString Q;
    QString A;
    QString B;
    QString C;
    QString D;
    QString Ans;

};


#endif // Q_ENTRY_H
