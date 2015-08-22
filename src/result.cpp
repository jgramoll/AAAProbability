#include "result.h"

Result::Result()
    : QObject()
    , m_attacker(new UnitArmy())
    , m_defender(new UnitArmy())
    , m_attackerIPCLost(0)
    , m_defenderIPCLost(0)
    , m_occurance(1)
    , m_probability(0)
    , m_resultType(Unknown)
{
}

QVariant Result::attackerVariant() const
{
    return QVariant::fromValue<QObject *>(m_attacker.data());
}
QSharedPointer<UnitArmy> Result::attacker() const
{
    return m_attacker;
}

QVariant Result::defenderVariant() const
{
    return QVariant::fromValue<QObject *>(m_defender.data());
}
QSharedPointer<UnitArmy> Result::defender() const
{
    return m_defender;
}

int Result::attackerIPCLost() const
{
    return m_attackerIPCLost;
}
void Result::setAttackerIPCLost(int attackerIPCLost)
{
    m_attackerIPCLost = attackerIPCLost;
}

int Result::defenderIPCLost() const
{
    return m_defenderIPCLost;
}
void Result::setDefenderIPCLost(int defenderIPCLost)
{
    m_defenderIPCLost = defenderIPCLost;
}

double Result::probability() const
{
    return m_probability;
}
Result::ResultType Result::resultType() const
{
    return m_resultType;
}

int Result::occurance() const
{
    return m_occurance;
}
void Result::addOccurance()
{
    ++m_occurance;
}
void Result::setProbability(int totalAttempts)
{
    m_probability = (double)m_occurance / totalAttempts;
    emit probabilityChanged();
}
void Result::setResultType(ResultType resultType)
{
    m_resultType = resultType;
}
