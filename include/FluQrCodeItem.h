/**
# @File     : FluQrCodeItem.h
# @Author   : jade
# @Date     : 2025/8/18 19:41
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluQrCodeItem.h
*/
//

#ifndef FLUQRCODEITEM_H
#define FLUQRCODEITEM_H

#include <QQuickPaintedItem>
#include <QPainter>
#include "include/stdafx.h"

/**
 * @brief The FluQrCodeItem class
 */
class FluQrCodeItem : public QQuickPaintedItem {
    Q_OBJECT

    Q_PROPERTY_AUTO(QString, text)
    Q_PROPERTY_AUTO(QColor, color)
    Q_PROPERTY_AUTO(QColor, bgColor)
    Q_PROPERTY_AUTO(int, size)
    QML_NAMED_ELEMENT(FluQrCodeItem)
public:
    explicit FluQrCodeItem(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;
};

#endif //FLUQRCODEITEM_H
