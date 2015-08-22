#ifndef SORTMODEL_H
#define SORTMODEL_H

#include <QModelIndex>
#include <QSortFilterProxyModel>
#include <QVariant>

#include <functional>

class SortModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    SortModel(QObject *parent = 0);
    virtual ~SortModel();

    void setSortFunc(int sortRole, const std::function <QVariant (const QVariant &item)>& func);

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

private:
    std::function <QVariant (const QVariant &item)> m_sortFunc;
    int m_sortRole;

};

#endif // SORTMODEL_H
