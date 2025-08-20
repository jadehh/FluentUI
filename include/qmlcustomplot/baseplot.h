/**
# @File     : baseplot.h
# @Author   : jade
# @Date     : 2025/8/18 17:32
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : baseplot.h
*/
//

#ifndef BASEPLOT_H
#define BASEPLOT_H

#include "include/qmlcustomplot/macros.h"
#include <QtGui/QColor>
#include <QtCore/QString>
#include <QtQuick/QQuickPaintedItem>

class QCustomPlot;

namespace QmlQCustomPlot
{

class Axis;
class Graph;
class BasePlot : public QQuickPaintedItem
{
    Q_OBJECT
    QML_READ_WRITE_NOTIFY_PROPERTY(QColor, backgroundColor)
    QML_READ_NOTIFY_PROPERTY(QmlQCustomPlot::Axis *, xAxis)
    QML_READ_NOTIFY_PROPERTY(QmlQCustomPlot::Axis *, x1Axis)
    QML_READ_NOTIFY_PROPERTY(QmlQCustomPlot::Axis *, yAxis)
    QML_READ_NOTIFY_PROPERTY(QmlQCustomPlot::Axis *, y1Axis)
    QML_ELEMENT
    Q_PROPERTY(QVariantMap graphs READ graphs NOTIFY graphsChanged)
public:
    BasePlot(QQuickItem *parent = nullptr);
    ~BasePlot() override;

    void set_backgroundColor(const QColor &value);
    QVariantMap graphs() const;
    Q_SIGNAL void graphsChanged();
    Q_INVOKABLE void addGraph(const QString &key);
    Q_INVOKABLE void removeGraph(const QString &key);
    Q_INVOKABLE void rescaleAxes(bool onlyVisiblePlottables=false) const;

    void paint(QPainter *painter) override;
    QCustomPlot *customPlot() const { return m_customPlot; }
    const QMap<QString, Graph *> &graphsMap() const { return m_graphs; }
    Graph* getGraph(const QString &key) const;

protected:
    virtual void onChartViewReplot() { update(); }
    virtual void onChartViewSizeChanged();

    virtual void hoverMoveEvent(QHoverEvent *event) override { Q_UNUSED(event) }
    virtual void mousePressEvent(QMouseEvent *event) override { routeMouseEvents(event); }
    virtual void mouseReleaseEvent(QMouseEvent *event) override { routeMouseEvents(event); }
    virtual void mouseMoveEvent(QMouseEvent *event) override { routeMouseEvents(event); }
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override { routeMouseEvents(event); }
    virtual void wheelEvent(QWheelEvent *event) override { routeWheelEvents(event); }
    void routeMouseEvents(const QMouseEvent *event) const;
    void routeWheelEvents(const QWheelEvent *event) const;

private:
    QCustomPlot *m_customPlot = nullptr;
    QMap<QString, Graph *> m_graphs;
};

} // namespace QmlQCustomPlot

#endif //BASEPLOT_H
