#ifndef IUNIT
#define IUNIT

#include <QObject>

class IUnit : public QObject
{
    Q_OBJECT
    Q_ENUMS(UnitType)

    Q_PROPERTY(UnitType unitType READ unitType CONSTANT FINAL)
    Q_PROPERTY(QString name READ name CONSTANT FINAL)
    Q_PROPERTY(int attackValue READ attackValue CONSTANT FINAL)
    Q_PROPERTY(int defendValue READ defendValue CONSTANT FINAL)
    Q_PROPERTY(int cost READ cost CONSTANT FINAL)

public:

    enum UnitType {
        Infantry,
        Tank,
        Fighter,
        Bomber
    };

    virtual UnitType unitType() const = 0;
    virtual const QString &name() const = 0;
    virtual int attackValue() const = 0;
    virtual int defendValue() const = 0;
    virtual int cost() const = 0;

};

#endif // IUNIT

