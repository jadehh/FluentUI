/**
# @File     : FluentUI.h
# @Author   : jade
# @Date     : 2025/8/18 19:38
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluentUI.h
*/
//

#ifndef FLUENTUI_H
#define FLUENTUI_H
#pragma once

#include <QObject>
#include <QQmlEngine>

#include "FluHotReloadManager.h"

/**
 * @brief The FluentUI class
 */
class FluentUI{

public:

    static Q_DECL_EXPORT void registerTypes(const QQmlEngine *engin);
    static void registerTypes(const char *uri);
    static Q_DECL_EXPORT void initHotReloader(QQmlApplicationEngine *engine, const QUrl& mainUrlPath,const char* uri, int major, int minor,const char* rootPath,const char* singleQmlPath,const char* watchQmlPath);
    static void initializeEngine(const QQmlEngine *engine, [[maybe_unused]] const char *uri);
    static Q_DECL_EXPORT void registerSingleTypes();
    static Q_DECL_EXPORT void enableHotReloader();

private:
    static FLuHotReloadManager *hotReloadManager;
    static constexpr int _major = 1;
    static constexpr int _minor = 0;
    static const char *_uri;
};

#endif //FLUENTUI_H
