#ifndef AAAPROBABILITY_H
#define AAAPROBABILITY_H

#include <QHash>
#include <QList>
#include <QQuickView>
#include <QPointer>
#include <QSharedPointer>
#include <QtConcurrent>

#include "HashModel.h"
#include "Result.h"
#include "SortModel.h"
#include "UnitArmy.h"

class AAAProbability : public QQuickView
{
    Q_OBJECT
    Q_ENUMS(PanelState)

    Q_PROPERTY(PanelState panelState READ panelState WRITE setPanelState NOTIFY panelStateChanged FINAL)
    Q_PROPERTY(QVariant attacker READ attackerVariant CONSTANT FINAL)
    Q_PROPERTY(QVariant defender READ defenderVariant CONSTANT FINAL)
    Q_PROPERTY(double probability READ probability NOTIFY probabilityChanged FINAL)
    Q_PROPERTY(double attackerAverageLostIPC READ attackerAverageLostIPC NOTIFY attackerAverageLostIPCChanged FINAL)
    Q_PROPERTY(double defenderAverageLostIPC READ defenderAverageLostIPC NOTIFY defenderAverageLostIPCChanged FINAL)
    Q_PROPERTY(QVariant results READ resultsVariant CONSTANT FINAL)
    Q_PROPERTY(QVariant sortedResults READ sortedResults CONSTANT FINAL)
    Q_PROPERTY(bool processing READ processing NOTIFY processingChanged FINAL)

public:
    explicit AAAProbability(QWindow *parent = 0);

    enum PanelState {
        UnitForm,
        Results
    };

    PanelState panelState() const;
    void setPanelState(PanelState panelState);

    QVariant attackerVariant() const;
    UnitArmy &attacker() const;

    QVariant defenderVariant() const;
    UnitArmy &defender() const;

    double probability() const;
    double attackerAverageLostIPC() const;
    double defenderAverageLostIPC() const;

    QVariant resultsVariant() const;
    QSharedPointer<HashModel<Result> > results() const;
    QVariant sortedResults() const;

    bool processing() const;

    Q_INVOKABLE void calculateLand();
    Q_INVOKABLE void navigateToForm();

signals:
    void panelStateChanged() const;
    void probabilityChanged() const;
    void attackerAverageLostIPCChanged() const;
    void defenderAverageLostIPCChanged() const;
    void processingChanged() const;

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    PanelState m_panelState;
    QPointer<UnitArmy> m_attacker;
    QPointer<UnitArmy> m_defender;
    double m_probability;
    double m_attackerAverageLostIPC;
    double m_defenderAverageLostIPC;
    QSharedPointer<HashModel<Result> > m_resultsModel;
    QSharedPointer<SortModel> m_resultsSortModel;
    bool m_processing;

    void setProbability(double probability);
    void setAttackerAverageLostIPC(double attackerAverageLostIPC);
    void setDefenderAverageLostIPC(double defenderAverageLostIPC);
    void setProcessing(bool processing);

    bool simulate();
    void setResults(QSharedPointer<Result> result, const QList<QSharedPointer<IUnit>> &attackers, const QList<QSharedPointer<IUnit>> &defenders);

};

#endif // AAAPROBABILITY_H
