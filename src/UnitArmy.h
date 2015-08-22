#ifndef UNITARMY_H
#define UNITARMY_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "IUnit.h"

class UnitArmy : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int infantryCount READ infantryCount WRITE setInfantryCount NOTIFY infantryCountChanged FINAL)
    Q_PROPERTY(int tankCount READ tankCount WRITE setTankCount NOTIFY tankCountChanged FINAL)
    Q_PROPERTY(int fighterCount READ fighterCount WRITE setFighterCount NOTIFY fighterCountChanged FINAL)
    Q_PROPERTY(int bomberCount READ bomberCount WRITE setBomberCount NOTIFY bomberCountChanged FINAL)

public:
    explicit UnitArmy(QObject *parent = 0);

    int infantryCount() const;
    void setInfantryCount(int infantryCount);

    int tankCount() const;
    void setTankCount(int tankCount);

    int fighterCount() const;
    void setFighterCount(int tankCount);

    int bomberCount() const;
    void setBomberCount(int bomberCount);

    void fromList(const QList<QSharedPointer<IUnit>> &units);
    QString toString() const;

signals:
    void infantryCountChanged() const;
    void tankCountChanged() const;
    void fighterCountChanged() const;
    void bomberCountChanged() const;

private:
    int m_infantryCount;
    int m_tankCount;
    int m_fighterCount;
    int m_bomberCount;

};

#endif // UNITARMY_H
