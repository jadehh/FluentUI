/**
# @File     : QLogger.h
# @Author   : jade
# @Date     : 2025/9/4 12:54
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : QLogger.h
*/
#pragma once
#include <QObject>
#include <QString>
#include "singleton.h"

class FluLogger : public QObject {
    Q_OBJECT
public:
    explicit FluLogger(QObject *parent = nullptr);
    ~FluLogger() override ;
    static  QString getQString(const QJSValue &value);
    SINGLETON(FluLogger)

public slots:
    static void trace(const QJSValue &value);
    static void debug(const QJSValue &value);
    static void info(const QJSValue &value);
    static void warning(const QJSValue &value);
    static void error(const QJSValue &value);
};
