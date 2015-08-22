#ifndef HASHMODELBASE_H
#define HASHMODELBASE_H

#include <QAbstractListModel>
#include <QHash>
#include <QSharedPointer>

class HashModelBase : public QAbstractListModel
{

public:
    HashModelBase(QObject *parent = 0);
    virtual ~HashModelBase();

    enum Roles {
        item = Qt::UserRole
    };

    QSharedPointer<QObject> find(const QString &key);
    void insert(const QString &key, const QSharedPointer<QObject> &value);
    void clear();

    QList<QString> keys() const;
    bool contains(const QString &key) const;

    //QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

protected:
    QHash<QString, QSharedPointer<QObject> > m_objectList;

private:
    QHash<int, QByteArray> m_roleNames;

    QHash<int, QString> m_index;

};

#endif // HASHMODELBASE_H
