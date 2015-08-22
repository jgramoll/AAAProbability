#include "Fighter.h"

const QString Fighter::m_name = "Fighter";

IUnit::UnitType Fighter::unitType() const
{
    return IUnit::Fighter;
}
const QString &Fighter::name() const
{
    return m_name;
}
int Fighter::attackValue() const
{
    return 3;
}
int Fighter::defendValue() const
{
    return 4;
}
int Fighter::cost() const
{
    return 10;
}

