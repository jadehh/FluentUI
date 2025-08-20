/**
# @File     : FluTableModel.cpp
# @Author   : jade
# @Date     : 2025/8/18 20:36
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluTableModel.cpp
*/
//
#include "include/FluTableModel.h"

FluTableModel::FluTableModel(QObject *parent) : QAbstractTableModel{parent} {
}

int FluTableModel::rowCount(const QModelIndex &parent) const {
    return _rows.count();
}


int FluTableModel::columnCount(const QModelIndex &parent) const {
    return this->_columnSource.size();
}

QVariant FluTableModel::data(const QModelIndex &index, int role) const {
    switch (role) {
    case FluTableModel::RowModel:
        return QVariant::fromValue(_rows.at(index.row()));
    case FluTableModel::ColumnModel:
        return QVariant::fromValue(_columnSource.at(index.column()));
    default:
        break;
    }
    return {};
}

QHash<int, QByteArray> FluTableModel::roleNames() const {
    return {
            {FluTableModel::RowModel,    "rowModel"   },
            {FluTableModel::ColumnModel, "columnModel"}
    };
}

void FluTableModel::clear() {
    beginResetModel();
    this->_rows.clear();
    endResetModel();
}

QVariant FluTableModel::getRow(const int rowIndex) const
{
    return _rows.at(rowIndex);
}

void FluTableModel::setRow(const int rowIndex, const QVariant& row) {
    _rows.replace(rowIndex, row.toMap());
    Q_EMIT dataChanged(index(rowIndex, 0), index(rowIndex, columnCount() - 1));
}

void FluTableModel::insertRow(const int rowIndex, const QVariant& row) {
    beginInsertRows(QModelIndex(), rowIndex, rowIndex);
    _rows.insert(rowIndex, row.toMap());
    endInsertRows();
}

void FluTableModel::removeRow(const int rowIndex, const int rows) {
    beginRemoveRows(QModelIndex(), rowIndex, rowIndex + rows - 1);
    _rows = _rows.mid(0, rowIndex) + _rows.mid(rowIndex + rows);
    endRemoveRows();
}

void FluTableModel::appendRow(const QVariant& row) {
    insertRow(rowCount(), row);
}
