#ifndef FIGHTER_H
#define FIGHTER_H

#include "IUnit.h"

class Fighter : public IUnit
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

#endif // FIGHTER_H
