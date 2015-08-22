#include "Tank.h"

const QString Tank::m_name = "Tank";

IUnit::UnitType Tank::unitType() const
{
    return IUnit::Tank;
}
const QString &Tank::name() const
{
    return m_name;
}
int Tank::attackValue() const
{
    return 3;
}
int Tank::defendValue() const
{
    return 3;
}
int Tank::cost() const
{
    return 6;
}

