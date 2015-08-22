#include "Infantry.h"

const QString Infantry::m_name = "Infantry";

IUnit::UnitType Infantry::unitType() const
{
    return IUnit::Infantry;
}
const QString &Infantry::name() const
{
    return m_name;
}
int Infantry::attackValue() const
{
    return 1;
}
int Infantry::defendValue() const
{
    return 2;
}
int Infantry::cost() const
{
    return 3;
}

