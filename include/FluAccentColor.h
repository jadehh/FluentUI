/**
# @File     : FluAccentColor.h
# @Author   : jade
# @Date     : 2025/8/18 19:34
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluAccentColor.h
*/
//

#ifndef FLUACCENTCOLOR_H
#define FLUACCENTCOLOR_H
#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <QColor>
#include "include/stdafx.h"

/**
 * @brief The FluAccentColor class
 */
class FluAccentColor  : public QObject {
    Q_OBJECT

    Q_PROPERTY_AUTO(QColor, darkest)
    Q_PROPERTY_AUTO(QColor, darker)
    Q_PROPERTY_AUTO(QColor, dark)
    Q_PROPERTY_AUTO(QColor, normal)
    Q_PROPERTY_AUTO(QColor, light)
    Q_PROPERTY_AUTO(QColor, lighter)
    Q_PROPERTY_AUTO(QColor, lightest)
    QML_NAMED_ELEMENT(FluAccentColor)
public:
    explicit FluAccentColor(QObject *parent = nullptr);
};

#endif //FLUACCENTCOLOR_H
