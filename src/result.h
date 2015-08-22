#ifndef RESULT_H
#define RESULT_H

#include <QObject>
#include <QSharedPointer>
#include <QVariant>

#include "IUnit.h"
#include "ListModel.h"
#include "UnitArmy.h"

class Result : public QObject
{
    Q_OBJECT
    Q_ENUMS(ResultType)

    Q_PROPERTY (QVariant attacker READ attackerVariant CONSTANT FINAL)
    Q_PROPERTY (QVariant defender READ defenderVariant CONSTANT FINAL)
    Q_PROPERTY (QVariant attackerIPCLost READ attackerIPCLost CONSTANT FINAL)
    Q_PROPERTY (QVariant defenderIPCLost READ attackerIPCLost CONSTANT FINAL)
    Q_PROPERTY (double probability READ probability NOTIFY probabilityChanged FINAL)
    Q_PROPERTY (ResultType resultType READ resultType CONSTANT FINAL)

public:
    explicit Result();

    enum ResultType {
        Unknown,
        Attacker,
        Defender,
        Tie,
        Retreat
    };

    QVariant attackerVariant() const;
    QSharedPointer<UnitArmy> attacker() const;

    QVariant defenderVariant() const;
    QSharedPointer<UnitArmy> defender() const;

    int attackerIPCLost() const;
    void setAttackerIPCLost(int attackerIPCLost);

    int defenderIPCLost() const;
    void setDefenderIPCLost(int defenderIPCLost);

    double probability() const;
    ResultType resultType() const;

    int occurance() const;
    void addOccurance();

    void setProbability(int totalAttempts);
    void setResultType(ResultType resultType);

signals:
    void probabilityChanged() const;

private:
    QSharedPointer<UnitArmy> m_attacker;
    QSharedPointer<UnitArmy> m_defender;
    int m_attackerIPCLost;
    int m_defenderIPCLost;
    int m_occurance;
    double m_probability;
    ResultType m_resultType;

};

#endif // RESULT_H
