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

/**
 * @brief The FluentUI class
 */
class FluentUI{

public:

    static Q_DECL_EXPORT void registerTypes(const QQmlEngine *engine);

    static void registerTypes(const char *uri);

    static void initializeEngine(const QQmlEngine *engine, [[maybe_unused]] const char *uri);

private:
    static constexpr int _major = 1;
    static constexpr int _minor = 0;
    static const char *_uri;
};

#endif //FLUENTUI_H
