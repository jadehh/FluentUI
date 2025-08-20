/**
# @File     : fluentuiplugin.h
# @Author   : jade
# @Date     : 2025/8/18 19:38
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : fluentuiplugin.h
*/
//

#ifndef FLUENTUIPLUGIN_H
#define FLUENTUIPLUGIN_H

#include <QQmlExtensionPlugin>

/**
 * @brief The FluentUIPlugin class
 */
class FluentUIPlugin final : public QQmlExtensionPlugin {
    Q_OBJECT

    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    FluentUIPlugin();

    void registerTypes(const char *uri) Q_DECL_OVERRIDE;

    void initializeEngine(QQmlEngine *engine, const char *uri) Q_DECL_OVERRIDE;
};

#endif //FLUENTUIPLUGIN_H
