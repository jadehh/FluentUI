/**
# @File     : FluFluWindowController.cpp
# @Author   : jade
# @Date     : 2025/8/21 09:07
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluFluWindowController.cpp
*/
//

#include "include/FluWindowController.h"

FluWindowController::FluWindowController(QObject *parent) : QObject(parent) {}

void FluWindowController::setupWindow(QQuickWindow *window)
{
    m_window = window;

    if (m_window) {
        connectWindowSignals();
        updateUIScale();
    }
}

qreal FluWindowController::uiScale() const { return m_uiScale; }
int FluWindowController::windowWidth() const { return m_window ? m_window->width() : 800; }
int FluWindowController::windowHeight() const { return m_window ? m_window->height() : 600; }

void FluWindowController::connectWindowSignals()
{
    if (!m_window) return;

    // 断开旧连接
    disconnect(m_window, nullptr, this, nullptr);

    // 连接新信号
    connect(m_window, &QQuickWindow::widthChanged, this, [this](){
        updateUIScale();
        emit windowSizeChanged();
    });

    connect(m_window, &QQuickWindow::heightChanged, this, [this](){
        updateUIScale();
        emit windowSizeChanged();
    });
}

void FluWindowController::updateUIScale()
{
    if (!m_window) return;

    const qreal refWidth = 1280.0;
    const qreal refHeight = 720.0;

    qreal newScale = qMin(m_window->width() / refWidth,
                         m_window->height() / refHeight);
    newScale = qBound(0.5, newScale, 2.0); // 限制在0.5-2.0倍之间

    if (!qFuzzyCompare(m_uiScale, newScale)) {
        m_uiScale = newScale;
        qDebug() << "FluWindowController::updateUIScale" << m_uiScale;

        emit uiScaleChanged();
    }
}