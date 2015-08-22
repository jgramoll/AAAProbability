#include "HashModelBase.h"

HashModelBase::HashModelBase(QObject *parent /*= 0*/)
    : QAbstractListModel(parent)
    , m_roleNames(QAbstractListModel::roleNames())
    , m_objectList()
{
    m_roleNames.insert(item, "item");
}
HashModelBase::~HashModelBase(){
}

QSharedPointer<QObject> HashModelBase::find(const QString &key)
{
    return *m_objectList.find(key);
}

void HashModelBase::insert(const QString &key, const QSharedPointer<QObject> &value)
{
    int row = m_objectList.count();
    beginInsertRows(QModelIndex(), row, row);

    m_objectList.insert(key, value);
    m_index.insert(row, key);

    endInsertRows();
}
void HashModelBase::clear()
{
    beginResetModel();
    m_objectList.clear();
    endResetModel();
}

QList<QString> HashModelBase::keys() const
{
    return m_objectList.keys();
}
bool HashModelBase::contains(const QString &key) const
{
    return m_objectList.contains(key);
}

//QAbstractListModel overrides
int HashModelBase::rowCount(const QModelIndex &/*parent = QModelIndex()*/) const
{
    return m_objectList.count();
}
QVariant HashModelBase::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
    if (!index.isValid() || index.row() > m_objectList.count())
        return QVariant();

    switch(role)
    {
    case item:
        return QVariant::fromValue<QObject *>(m_objectList[m_index[index.row()]].data());
    }

    return QVariant();
}
QHash<int, QByteArray> HashModelBase::roleNames() const
{
    return m_roleNames;
}
