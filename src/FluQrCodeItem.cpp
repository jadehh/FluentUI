/**
# @File     : FluQrCodeItem.cpp
# @Author   : jade
# @Date     : 2025/8/18 20:35
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluQrCodeItem.cpp
*/
//
#include "include/FluQrCodeItem.h"


FluQrCodeItem::FluQrCodeItem(QQuickItem *parent) : QQuickPaintedItem(parent) {
    _color = QColor(0, 0, 0, 255);
    _bgColor = QColor(255, 255, 255, 255);
    _size = 100;
    setWidth(_size);
    setHeight(_size);
    connect(this, &FluQrCodeItem::textChanged, this, [=] { update(); });
    connect(this, &FluQrCodeItem::colorChanged, this, [=] { update(); });
    connect(this, &FluQrCodeItem::bgColorChanged, this, [=] { update(); });
    connect(this, &FluQrCodeItem::sizeChanged, this, [=] {
        setWidth(_size);
        setHeight(_size);
        update();
    });
}

void FluQrCodeItem::paint(QPainter *painter) {
    if (_text.isEmpty()) {
        return;
    }
    if (_text.length() > 1024) {
        return;
    }
    painter->save();
    //
    // painter->drawPixmap(QRect(0, 0, static_cast<int>(width()), static_cast<int>(height())), pixmap);
    // painter->restore();
}
