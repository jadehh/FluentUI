/**
# @File     : FluFluWindowController.h
# @Author   : jade
# @Date     : 2025/8/21 09:07
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluWindowController.h
*/
//

#ifndef FLUWINDOWCONTROLLER_H
#define FLUWINDOWCONTROLLER_H
#include <QObject>
#include <QQuickWindow>
#include <QQuickItem>

#include "singleton.h"

class FluWindowController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal uiScale READ uiScale NOTIFY uiScaleChanged)
    Q_PROPERTY(int windowWidth READ windowWidth NOTIFY windowSizeChanged)
    Q_PROPERTY(int windowHeight READ windowHeight NOTIFY windowSizeChanged)

public:
    SINGLETON(FluWindowController);


    // 设置主窗口（从FluLauncher调用）
    Q_INVOKABLE void setupWindow(QQuickWindow *window);

    qreal uiScale() const;
    int windowWidth() const;
    int windowHeight() const;

    signals:
        void uiScaleChanged();
    void windowSizeChanged();

private:
    explicit FluWindowController(QObject *parent = nullptr);
    QQuickWindow *m_window = nullptr;
    qreal m_uiScale = 1.0;

    void updateUIScale();
    void connectWindowSignals();
};



#endif //FLUWINDOWCONTROLLER_H
