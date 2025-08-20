/**
# @File     : FluApp.cpp
# @Author   : jade
# @Date     : 2025/8/18 19:46
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluApp.cpp
*/
//
#include "include/FluApp.h"
#include <QGuiApplication>
#include <QQuickItem>
#include <QTimer>
#include <QFontDatabase>
#include <QJsonObject>
#include <QQmlEngine>
#include <QTranslator>
#include <utility>
#include "include/FluentIconDef.h"

FluApp::FluApp(QObject *parent) : QObject{parent}, _launcher(nullptr)
{
    _useSystemAppBar = false;
}

FluApp::~FluApp() = default;

void FluApp::init(QObject *launcher, QLocale locale) {
    this->launcher(launcher);
    _locale = std::move(locale);
    _engine = qmlEngine(launcher);
    _translator = new QTranslator(this);
    QGuiApplication::installTranslator(_translator);
    const QStringList uiLanguages = _locale.uiLanguages();
    for (const QString &name : uiLanguages) {
        if (const QString baseName = "fluentui_" + QLocale(name).name(); _translator->load(":/qt/qml/FluentUI/i18n/" + baseName)) {
            _engine->retranslate();
            break;
        }
    }
}

[[maybe_unused]] QJsonArray FluApp::iconData(const QString &keyword) {
    QJsonArray arr;
    const QMetaEnum enumType = FluentIcons::staticMetaObject.enumerator(
        FluentIcons::staticMetaObject.indexOfEnumerator("Type"));
    for (int i = 0; i <= enumType.keyCount() - 1; ++i) {
        QString name = enumType.key(i);
        const int icon = enumType.value(i);
        if (keyword.isEmpty() || name.contains(keyword)) {
            QJsonObject obj;
            obj.insert("name", name);
            obj.insert("icon", icon);
            arr.append(obj);
        }
    }
    return arr;
}
