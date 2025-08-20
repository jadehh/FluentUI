/**
# @File     : FluTableModel.h
# @Author   : jade
# @Date     : 2025/8/18 19:41
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluTableModel.h
*/
//

#ifndef FLUTABLEMODEL_H
#define FLUTABLEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QtQml/qqml.h>
#include "stdafx.h"

class FluTableModel  : public QAbstractTableModel {
    Q_OBJECT
    Q_PROPERTY_AUTO(QList<QVariantMap>, columnSource)
    Q_PROPERTY_AUTO(QList<QVariantMap>, rows)
    Q_PROPERTY(int rowCount READ rowCount CONSTANT)
    QML_NAMED_ELEMENT(FluTableModel)
public:
    enum TableModelRoles { RowModel = 0x0101, ColumnModel = 0x0102 };


    explicit FluTableModel(QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent = {}) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent = {}) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index,
                                int role = Qt::DisplayRole) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void clear();

    Q_INVOKABLE QVariant getRow(int rowIndex) const;

    Q_INVOKABLE void setRow(int rowIndex, const QVariant& row);

    Q_INVOKABLE void insertRow(int rowIndex, const QVariant& row);

    Q_INVOKABLE void removeRow(int rowIndex, int rows = 1);

    Q_INVOKABLE void appendRow(const QVariant& row);
};



#endif //FLUTABLEMODEL_H
