#include "UnitArmy.h"

UnitArmy::UnitArmy(QObject *parent /*= 0*/)
    : QObject(parent)
    , m_infantryCount(0)
    , m_tankCount(0)
    , m_fighterCount(0)
    , m_bomberCount(0)
{
}

int UnitArmy::infantryCount() const
{
    return m_infantryCount;
}
void UnitArmy::setInfantryCount(int infantryCount)
{
    if (m_infantryCount == infantryCount) return;
    m_infantryCount = infantryCount;
    emit infantryCountChanged();
}

int UnitArmy::tankCount() const
{
    return m_tankCount;
}
void UnitArmy::setTankCount(int tankCount)
{
    if (m_tankCount == tankCount) return;
    m_tankCount = tankCount;
    emit tankCountChanged();
}

int UnitArmy::fighterCount() const
{
    return m_fighterCount;
}
void UnitArmy::setFighterCount(int fighterCount)
{
    if (m_fighterCount == fighterCount) return;
    m_fighterCount = fighterCount;
    emit fighterCountChanged();
}

int UnitArmy::bomberCount() const
{
    return m_bomberCount;
}
void UnitArmy::setBomberCount(int bomberCount)
{
    if (m_bomberCount == bomberCount) return;
    m_bomberCount = bomberCount;
    emit bomberCountChanged();
}

void UnitArmy::fromList(const QList<QSharedPointer<IUnit>> &units)
{
    m_infantryCount = 0;
    m_tankCount = 0;
    m_fighterCount = 0;
    m_bomberCount = 0;

    auto itrEnd = units.cend();
    for (auto itr = units.cbegin(); itr != itrEnd; ++itr)
    {
        switch ((*itr)->unitType())
        {
        case IUnit::Infantry:
            ++m_infantryCount;
            break;
        case IUnit::Tank:
            ++m_tankCount;
            break;
        case IUnit::Fighter:
            ++m_fighterCount;
            break;
        case IUnit::Bomber:
            ++m_bomberCount;
            break;
        }
    }
}
QString UnitArmy::toString() const
{
     return QString("%1_%2_%3_%4").arg(m_infantryCount).arg(m_tankCount).arg(m_fighterCount).arg(m_bomberCount);
}

