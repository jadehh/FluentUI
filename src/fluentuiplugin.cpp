/**
# @File     : fluentuiplugin.cpp
# @Author   : jade
# @Date     : 2025/8/18 20:33
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : fluentuiplugin.cpp
*/
//
#include "include/fluentuiplugin.h"

#include "include/FluentUI.h"

FluentUIPlugin::FluentUIPlugin() = default;

void FluentUIPlugin::registerTypes(const char *uri) {
    FluentUI::registerTypes(uri);
}

void FluentUIPlugin::initializeEngine(QQmlEngine *engine, const char *uri) {
    FluentUI::initializeEngine(engine, uri);
}
