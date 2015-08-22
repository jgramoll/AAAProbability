#include "SortModel.h"

SortModel::SortModel(QObject *parent /*= 0*/)
    : QSortFilterProxyModel(parent)
    , m_sortFunc()
    , m_sortRole(Qt::DisplayRole)
{
}
SortModel::~SortModel(){
}

void SortModel::setSortFunc(int sortRole, const std::function <QVariant (const QVariant &item)>& func)
{
    m_sortRole = sortRole;
    m_sortFunc = func;
}

bool SortModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    auto leftData = sourceModel()->data(left , m_sortRole);
    auto rightData = sourceModel()->data(right , m_sortRole);

    if (!m_sortFunc)
        return leftData < rightData;

    return m_sortFunc(leftData) < m_sortFunc(rightData);
}
