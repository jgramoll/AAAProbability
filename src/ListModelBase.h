#ifndef LISTMODELBASE_H
#define LISTMODELBASE_H

#include <QAbstractListModel>
#include <QHash>
#include <QSharedPointer>

class ListModelBase : public QAbstractListModel
{

public:
    ListModelBase(QObject *parent = 0);
    virtual ~ListModelBase();

    enum Roles {
        item = Qt::UserRole
    };

    QSharedPointer<QObject> at(int i) const;
    void append(QSharedPointer<QObject> item);
    void removeFirst();
    void clear();

    //QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

private:
    QHash<int, QByteArray> m_roleNames;

    QList<QSharedPointer<QObject> > m_objectList;

};

#endif // LISTMODELBASE_H
