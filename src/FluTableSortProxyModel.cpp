/**
# @File     : FluTableSortProxyModel.cpp
# @Author   : jade
# @Date     : 2025/8/18 20:30
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluTableSortProxyModel.cpp
*/
//
#include "include/FluTableSortProxyModel.h"

#include <QJSValueList>

FluTableSortProxyModel::FluTableSortProxyModel(QSortFilterProxyModel *parent)
    : QSortFilterProxyModel{parent} {
    connect(this, &FluTableSortProxyModel::modelChanged, this,
            [=] { setSourceModel(this->model().value<QAbstractTableModel *>()); });
}

bool FluTableSortProxyModel::filterAcceptsRow(const int sourceRow,
                                              const QModelIndex &sourceParent) const {
    QJSValue filter = _filter;
    if (filter.isUndefined()) {
        return true;
    }
    QJSValueList data;
    data << sourceRow;
    return filter.call(data).toBool();
}

bool FluTableSortProxyModel::filterAcceptsColumn(int sourceColumn,
                                                 const QModelIndex &sourceParent) const {
    return true;
}

bool FluTableSortProxyModel::lessThan(const QModelIndex &sourceLeft,
                                      const QModelIndex &sourceRight) const {
    QJSValue comparator = _comparator;
    if (comparator.isUndefined()) {
        return true;
    }
    QJSValueList data;
    data << sourceLeft.row();
    data << sourceRight.row();
    bool flag = comparator.call(data).toBool();
    if (sortOrder() == Qt::AscendingOrder) {
        return !flag;
    } else {
        return flag;
    }
}

[[maybe_unused]] void FluTableSortProxyModel::setComparator(const QJSValue &comparator) {
    int column = 0;
    if (comparator.isUndefined()) {
        column = -1;
    }
    this->_comparator = comparator;
    if (sortOrder() == Qt::AscendingOrder) {
        sort(column, Qt::DescendingOrder);
    } else {
        sort(column, Qt::AscendingOrder);
    }
}

[[maybe_unused]] void FluTableSortProxyModel::setFilter(const QJSValue &filter) {
    this->_filter = filter;
    invalidateFilter();
}

[[maybe_unused]] QVariant FluTableSortProxyModel::getRow(const int rowIndex) const
{
    QVariant result;
    QMetaObject::invokeMethod(_model.value<QAbstractTableModel *>(), "getRow",
                              Q_RETURN_ARG(QVariant, result),
                              Q_ARG(int, mapToSource(index(rowIndex, 0)).row()));
    return result;
}

[[maybe_unused]] void FluTableSortProxyModel::setRow(const int rowIndex, const QVariant &val) const
{
    QMetaObject::invokeMethod(_model.value<QAbstractTableModel *>(), "setRow",
                              Q_ARG(int, mapToSource(index(rowIndex, 0)).row()),
                              Q_ARG(QVariant, val));
}

[[maybe_unused]] void FluTableSortProxyModel::insertRow(const int rowIndex, const QVariant &val) const
{
    QMetaObject::invokeMethod(_model.value<QAbstractTableModel *>(), "insertRow",
                              Q_ARG(int, mapToSource(index(rowIndex, 0)).row()),
                              Q_ARG(QVariant, val));
}

[[maybe_unused]] void FluTableSortProxyModel::removeRow(const int rowIndex, const int rows) const
{
    QMetaObject::invokeMethod(_model.value<QAbstractTableModel *>(), "removeRow",
                              Q_ARG(int, mapToSource(index(rowIndex, 0)).row()), Q_ARG(int, rows));
}
