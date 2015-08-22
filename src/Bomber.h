#ifndef BOMBER_H
#define BOMBER_H

#include "IUnit.h"

class Bomber : public IUnit
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

#endif // BOMBER_H
