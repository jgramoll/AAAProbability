#ifndef HASHMODEL_H
#define HASHMODEL_H

#include <QHashIterator>
#include <QMutableHashIterator>

#include "HashModelBase.h"

template <class T>
class HashModel : public HashModelBase
{

public:
    HashModel(QObject *parent = 0)
        : HashModelBase(parent)
    {
    }
    virtual ~HashModel(){}

    QSharedPointer<T> find(const QString &key)
    {
        QSharedPointer<QObject> obj = HashModelBase::find(key);
        return obj.objectCast<T>();
    }

    QHashIterator<QString, QSharedPointer<T>> constInterator() const {
        return QHashIterator<QString, QSharedPointer<T>>(m_objectList);
    }

};

#endif // HASHMODEL_H
