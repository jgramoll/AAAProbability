#ifndef TANK_H
#define TANK_H

#include "IUnit.h"

class Tank : public IUnit
{

public:
    virtual UnitType unitType() const;
    virtual const QString &name() const;
    virtual int attackValue() const;
    virtual int defendValue() const;
    virtual int cost() const;

private:
    static const QString m_name;
};

#endif // TANK_H
