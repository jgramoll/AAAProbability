#ifndef INFANTRY_H
#define INFANTRY_H

#include "IUnit.h"

class Infantry : public IUnit
{

public:
    UnitType unitType() const;
    const QString &name() const;
    int attackValue() const;
    int defendValue() const;
    int cost() const;

private:
    static const QString m_name;
};

#endif // INFANTRY_H
