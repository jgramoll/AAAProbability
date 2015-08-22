#include <QString>
#include <QtTest>

#include <QGuiApplication>

#include "AAAProbability.h"

class AAAProbabiliyTest : public QObject
{
    Q_OBJECT

public:
    AAAProbabiliyTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void calculateLand_data();
    void calculateLand();

private:
    QPointer<QGuiApplication> m_guiApp;
    QPointer<AAAProbability> m_probability;
};

AAAProbabiliyTest::AAAProbabiliyTest()
{
    int argc = 0;
    char *argv = "";
    m_guiApp = QPointer<QGuiApplication>(new QGuiApplication(argc, &argv));

    m_probability = QPointer<AAAProbability>(new AAAProbability());
}

void AAAProbabiliyTest::initTestCase()
{
}

void AAAProbabiliyTest::cleanupTestCase()
{
}

void AAAProbabiliyTest::calculateLand_data()
{
    QTest::addColumn<int>("attackerInfantry");
    QTest::addColumn<int>("defenderInfantry");
    QTest::addColumn<int>("attackerTank");
    QTest::addColumn<int>("defenderTank");
    QTest::addColumn<int>("attackerFighter");
    QTest::addColumn<int>("defenderFighter");
    QTest::addColumn<int>("attackerBomber");
    QTest::addColumn<int>("defenderBomber");
    QTest::newRow("infantry")   << 3 << 3 << 0 << 0 << 0 << 0 << 0 << 0;
    QTest::newRow("tank")       << 0 << 0 << 3 << 3 << 0 << 0 << 0 << 0;
    QTest::newRow("fighter")    << 0 << 0 << 0 << 0 << 3 << 3 << 0 << 0;
    QTest::newRow("bomber")     << 0 << 0 << 0 << 0 << 0 << 0 << 3 << 3;
}

void AAAProbabiliyTest::calculateLand()
{
    QFETCH(int, attackerInfantry);
    QFETCH(int, defenderInfantry);
    QFETCH(int, attackerTank);
    QFETCH(int, defenderTank);
    QFETCH(int, attackerFighter);
    QFETCH(int, defenderFighter);
    QFETCH(int, attackerBomber);
    QFETCH(int, defenderBomber);

    m_probability->attacker().setInfantryCount(attackerInfantry);
    m_probability->defender().setInfantryCount(defenderInfantry);
    m_probability->attacker().setTankCount(attackerTank);
    m_probability->defender().setTankCount(defenderTank);
    m_probability->attacker().setFighterCount(attackerFighter);
    m_probability->defender().setFighterCount(defenderFighter);
    m_probability->attacker().setBomberCount(attackerBomber);
    m_probability->defender().setBomberCount(defenderBomber);

    QBENCHMARK {
        m_probability->calculateLand();
    }

    qDebug() << m_probability->probability();
    auto r = m_probability->results();

    auto keys = r->keys();
    auto itrEnd = keys.cend();
    qDebug() << "key count " << keys.count();
    for (auto itr = keys.cbegin(); itr != itrEnd; ++itr)
    {
        qDebug() << *itr << " : " << r->find(*itr)->probability();
    }
}

QTEST_APPLESS_MAIN(AAAProbabiliyTest)

#include "tst_aaaprobabiliytest.moc"
