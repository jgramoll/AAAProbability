#include "ListModelBase.h"

ListModelBase::ListModelBase(QObject *parent /*= 0*/)
    : QAbstractListModel(parent)
    , m_roleNames(QAbstractListModel::roleNames())
    , m_objectList()
{
    m_roleNames.insert(item, "item");
}
ListModelBase::~ListModelBase(){
}

QSharedPointer<QObject> ListModelBase::at(int i) const
{
    return m_objectList.at(i);
}
void ListModelBase::append(QSharedPointer<QObject> item)
{
    int row = m_objectList.count();
    beginInsertRows(QModelIndex(), row, row);

    m_objectList.append(item);

    endInsertRows();
}
void ListModelBase::removeFirst()
{
    beginRemoveRows(QModelIndex(), 0, 0);

    m_objectList.removeFirst();

    endRemoveRows();
}
void ListModelBase::clear()
{
    beginResetModel();
    m_objectList.clear();
    endResetModel();
}

//QAbstractListModel overrides
int ListModelBase::rowCount(const QModelIndex &/*parent = QModelIndex()*/) const
{
    return m_objectList.count();
}
QVariant ListModelBase::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
    if (!index.isValid() || index.row() > m_objectList.count())
        return QVariant();

    switch(role)
    {
    case item:
        return QVariant::fromValue<QObject *>(m_objectList.at(index.row()).data());
    }

    return QVariant();
}
QHash<int, QByteArray> ListModelBase::roleNames() const
{
    return m_roleNames;
}
