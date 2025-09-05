/**
# @File     : FluLogger.cpp
# @Author   : jade
# @Date     : 2025/9/4 12:58
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluLogger.cpp
*/

#include <QVariant>
#include <QJSValue>
#include "jade_tools/jade_tools.h"
#include "include/FluLogger.h"
FluLogger::FluLogger(QObject* parent){}
FluLogger::~FluLogger()= default;

QString FluLogger::getQString(const QJSValue& value)
{
    if (value.isArray()) {
        // 处理数组参数
        QVariantList list = value.toVariant().toList();
        QStringList parts;
        for (const QVariant &arg : list) {
            parts << arg.toString();
        }
        return parts.join(" ");
    }
    return  value.toString();
}

void FluLogger::trace(const QJSValue &value)
{
    LOG_TRACE() << getQString(value).toStdString();
}
void FluLogger::debug(const QJSValue& value)
{
    LOG_DEBUG() << getQString(value).toStdString();
}
void FluLogger::info(const QJSValue& value)
{
    LOG_INFO()  << getQString(value).toStdString();
}
void FluLogger::warning(const QJSValue& value)
{
    LOG_WARN() << getQString(value).toStdString();
}
void FluLogger::error(const QJSValue& value)
{
    LOG_ERROR() << getQString(value).toStdString();
}






