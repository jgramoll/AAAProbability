#include "AAAProbability.h"

#include <QDebug>
#include <QQmlEngine>
#include <QtQml>
#include <QGuiApplication>

#include "Infantry.h"
#include "Tank.h"
#include "Fighter.h"
#include "Bomber.h"

AAAProbability::AAAProbability(QWindow *parent) : QQuickView(parent /*= 0*/)
  , m_panelState(AAAProbability::UnitForm)
  , m_attacker(new UnitArmy())
  , m_defender(new UnitArmy())
  , m_probability(0)
  , m_resultsModel(new HashModel<Result>())
  , m_resultsSortModel(new SortModel())
  , m_processing(false)
{
    qmlRegisterType<AAAProbability>("AAAProbability", 1, 0, "PanelState");
    qmlRegisterType<Result>("AAAProbability", 1, 0, "Result");

    m_attacker->setInfantryCount(3);
    m_defender->setInfantryCount(3);

    m_resultsSortModel->setSourceModel(m_resultsModel.data());
    m_resultsSortModel->setSortFunc(HashModel<Result>::item, [](const QVariant &item)->QVariant{
        Result *result = qobject_cast<Result *>(item.value<QObject *>());
        return result ? result->probability() : 0;
    });
}

AAAProbability::PanelState AAAProbability::panelState() const
{
    return m_panelState;
}
void AAAProbability::setPanelState(PanelState panelState)
{
    if (m_panelState == panelState) return;
    m_panelState = panelState;
    emit panelStateChanged();
}


void AAAProbability::calculateLand()
{
    m_resultsModel->clear();
    setProcessing(true);
    setPanelState(AAAProbability::Results);

    int successes = 0;
    int attempts = 2000;
    for (int i = 0; i < attempts; ++i)
    {
        if (simulate())
            ++successes;

        if (i % 100 == 0)
            QGuiApplication::processEvents();
    }
    setProbability((double)successes/attempts);

    long attackerIPCLost = 0;
    long defenderIPCLost = 0;

    auto keys = m_resultsModel->keys();
    auto itrEnd = keys.cend();
    for (auto itr = keys.cbegin(); itr != itrEnd; ++itr)
    {
        auto result = m_resultsModel->find(*itr);
        result->setProbability(attempts);
        attackerIPCLost += result->attackerIPCLost() * result->occurance();
        defenderIPCLost += result->defenderIPCLost() * result->occurance();
    }

    setAttackerAverageLostIPC((double) attackerIPCLost / attempts);
    setDefenderAverageLostIPC((double) defenderIPCLost / attempts);

    m_resultsSortModel->sort(0, Qt::AscendingOrder);
    m_resultsSortModel->sort(0, Qt::DescendingOrder);
    setProcessing(false);
}

bool AAAProbability::simulate()
{
    QSharedPointer<Result> result(new Result());
    int count;

    QList<QSharedPointer<IUnit>> attackers;
    QList<QSharedPointer<IUnit>> defenders;

    ///
    /// Attacker
    ///
    count = m_attacker->infantryCount();
    for (int i = 0; i < count; ++i)
        attackers.append(QSharedPointer<IUnit>(new Infantry()));

    count = m_attacker->tankCount();
    for (int i = 0; i < count; ++i)
        attackers.append(QSharedPointer<IUnit>(new Tank()));

    count = m_attacker->fighterCount();
    for (int i = 0; i < count; ++i)
        attackers.append(QSharedPointer<IUnit>(new Fighter()));

    count = m_attacker->bomberCount();
    for (int i = 0; i < count; ++i)
        attackers.append(QSharedPointer<IUnit>(new Bomber()));


    ///
    /// Defender
    ///
    count = m_defender->infantryCount();
    for (int i = 0; i < count; ++i)
        defenders.append(QSharedPointer<IUnit>(new Infantry()));

    count = m_defender->tankCount();
    for (int i = 0; i < count; ++i)
        defenders.append(QSharedPointer<IUnit>(new Tank()));

    count = m_defender->fighterCount();
    for (int i = 0; i < count; ++i)
        defenders.append(QSharedPointer<IUnit>(new Fighter()));

    count = m_defender->bomberCount();
    for (int i = 0; i < count; ++i)
        defenders.append(QSharedPointer<IUnit>(new Bomber()));

    int attackHits;
    int defendHits;
    int attackCount;
    int defendCount;
    int attackerIPCLost = 0;
    int defenderIPCLost = 0;

    for (int i = 0; ; ++i)
    {
        attackHits = 0;
        defendHits = 0;
        attackCount = attackers.count();
        defendCount = defenders.count();

        //roll attack dice
        auto itrEnd = attackers.cend();
        for (auto itr = attackers.cbegin(); itr != itrEnd; ++itr)
        {
            int roll = (qrand() % 6) + 1; //die roll 1-6
            if (roll <= (*itr)->attackValue())
                ++attackHits;

            if (attackHits == defendCount)
                break;
        }

        //roll defend dice
        itrEnd = defenders.cend();
        for (auto itr = defenders.cbegin(); itr != itrEnd; ++itr)
        {
            int roll = (qrand() % 6) + 1; //die roll 1-6
            if (roll <= (*itr)->defendValue())
                ++defendHits;

            if (defendHits == attackCount)
                break;
        }

        //defender casualties
        for (int j = 0; j < attackHits; ++j)
        {
            defenderIPCLost += defenders.at(0)->cost();
            defenders.removeFirst();
        }

        //attack casualties
        for (int j = 0; j < defendHits; ++j)
        {
            attackerIPCLost += attackers.at(0)->cost();
            attackers.removeFirst();
        }

        if (defendHits == attackCount)
        {
            setResults(result, attackers, defenders);
            result->setAttackerIPCLost(attackerIPCLost);
            result->setDefenderIPCLost(defenderIPCLost);

            if (attackHits == defendCount)
                result->setResultType(Result::Tie);
            else
                result->setResultType(Result::Defender);

            return false;
        }
        if (attackHits == defendCount)
        {
            setResults(result, attackers, defenders);
            result->setAttackerIPCLost(attackerIPCLost);
            result->setDefenderIPCLost(defenderIPCLost);
            result->setResultType(Result::Attacker);
            return true;
        }
    }
}
void AAAProbability::setResults(QSharedPointer<Result> result, const QList<QSharedPointer<IUnit>> &attackers, const QList<QSharedPointer<IUnit>> &defenders)
{
    result->attacker()->fromList(attackers);
    result->defender()->fromList(defenders);

    QString resultStr = QString("%1_%2").arg(result->attacker()->toString()).arg(result->defender()->toString());
    if (m_resultsModel->contains(resultStr))
    {
        m_resultsModel->find(resultStr)->addOccurance();
        result.clear();
    }
    else
    {
        m_resultsModel->insert(resultStr, result);
    }
}

void AAAProbability::navigateToForm()
{
    setPanelState(AAAProbability::UnitForm);
}

QVariant AAAProbability::attackerVariant() const
{
    return QVariant::fromValue<QObject *>(m_attacker.data());
}
UnitArmy &AAAProbability::attacker() const
{
    return *m_attacker.data();
}
QVariant AAAProbability::defenderVariant() const
{
    return QVariant::fromValue<QObject *>(m_defender.data());
}
UnitArmy &AAAProbability::defender() const
{
    return *m_defender.data();
}

double AAAProbability::probability() const
{
    return m_probability;
}
double AAAProbability::attackerAverageLostIPC() const
{
    return m_attackerAverageLostIPC;
}
double AAAProbability::defenderAverageLostIPC() const
{
    return m_defenderAverageLostIPC;
}

QVariant AAAProbability::resultsVariant() const
{
    return QVariant::fromValue<QObject *>(m_resultsModel.data());
}
 QSharedPointer<HashModel<Result> > AAAProbability::results() const
{
    return m_resultsModel;
}
 QVariant AAAProbability::sortedResults() const
 {
     return QVariant::fromValue<QObject *>(m_resultsSortModel.data());
 }

 bool AAAProbability::processing() const
 {
     return m_processing;
 }

void AAAProbability::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_R && e->modifiers() & Qt::ControlModifier)
    {
        engine()->clearComponentCache();
        setSource(source());
        e->accept();
        return;
    }

    QQuickView::keyPressEvent(e);
}

void AAAProbability::setProbability(double probability)
{
    if (m_probability == probability) return;
    m_probability = probability;
    emit probabilityChanged();
}
void AAAProbability::setAttackerAverageLostIPC(double attackerAverageLostIPC)
{
    if (m_attackerAverageLostIPC == attackerAverageLostIPC) return;
    m_attackerAverageLostIPC = attackerAverageLostIPC;
    emit attackerAverageLostIPCChanged();
}
void AAAProbability::setDefenderAverageLostIPC(double defenderAverageLostIPC)
{
    if (m_defenderAverageLostIPC == defenderAverageLostIPC) return;
    m_defenderAverageLostIPC = defenderAverageLostIPC;
    emit defenderAverageLostIPCChanged();
}

void AAAProbability::setProcessing(bool processing)
{
    if (m_processing == processing) return;
    m_processing = processing;
    emit processingChanged();
}
