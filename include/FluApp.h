/**
# @File     : FluApp.h
# @Author   : jade
# @Date     : 2025/8/18 19:35
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluApp.h
*/
//

#ifndef FLUAPP_H
#define FLUAPP_H

#include <QObject>
#include <QWindow>
#include <QtQml/qqml.h>
#include <QQmlContext>
#include <QTranslator>
#include <QQuickWindow>
#include <QJsonArray>
#include "stdafx.h"
#include "singleton.h"

/**
 * @brief The FluApp class
 */
class FluApp : public QObject {
    Q_OBJECT
    Q_PROPERTY_AUTO(bool, useSystemAppBar)
    Q_PROPERTY_AUTO(QString, windowIcon)
    Q_PROPERTY_AUTO(QLocale, locale)
    Q_PROPERTY_AUTO_P(QObject *, launcher)
    QML_NAMED_ELEMENT(FluApp)
    QML_SINGLETON

private:
    explicit FluApp(QObject *parent = nullptr);

    ~FluApp() override;

public:
    SINGLETON(FluApp)

    static FluApp *create(QQmlEngine *, QJSEngine *) {
        return getInstance();
    }

    Q_INVOKABLE void init(QObject *launcher, QLocale locale = QLocale::system());

    [[maybe_unused]] Q_INVOKABLE static QJsonArray iconData(const QString &keyword = "");

private:
    QQmlEngine *_engine{};
    QTranslator *_translator = nullptr;
};

#endif //FLUAPP_H
