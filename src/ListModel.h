#ifndef LISTMODEL_H
#define LISTMODEL_H

#include "ListModelBase.h"

template <class T>
class ListModel : public ListModelBase
{

public:
    ListModel(QObject *parent = 0)
        : ListModelBase(parent)
    {
    }
    virtual ~ListModel(){}

    QSharedPointer<T> at(int i) const
    {
        QSharedPointer<QObject> obj = ListModelBase::at(i);
        return obj.objectCast<T>();
    }

};

#endif // LISTMODEL_H
