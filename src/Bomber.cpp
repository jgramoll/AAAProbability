#include "Bomber.h"

const QString Bomber::m_name = "Bomber";

IUnit::UnitType Bomber::unitType() const
{
    return IUnit::Bomber;
}
const QString &Bomber::name() const
{
    return m_name;
}
int Bomber::attackValue() const
{
    return 4;
}
int Bomber::defendValue() const
{
    return 1;
}
int Bomber::cost() const
{
    return 12;
}

