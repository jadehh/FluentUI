/**
# @File     : TimePlot.cpp
# @Author   : jade
# @Date     : 2025/8/18 19:31
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : TimePlot.cpp
*/
//
#include "include/qmlcustomplot/TimePlot.h"
#include "include/qmlcustomplot/graph.h"
#include "include/qmlcustomplot/axis.h"
#include "include/qmlcustomplot/qcustomplot.h"

#include <QTimer>

namespace QmlQCustomPlot
{

TimePlot::TimePlot(QQuickItem *parent)
    : BasePlot(parent)
    , m_timer(new QTimer(this))
{
    xAxis()->setTickerType(Axis::Time);
    connect(m_timer, &QTimer::timeout, this, &TimePlot::onTimeOut);
    m_timer->start(5);
    startTimer(25);
    m_plotTimeRangeInMilliseconds = 60;
}

TimePlot::~TimePlot()
{
}

void TimePlot::set_plotTimeRangeInMilliseconds(const int value) noexcept
{
    if(m_plotTimeRangeInMilliseconds != value) {
        m_plotTimeRangeInMilliseconds = value;
        emit plotTimeRangeInMillisecondsChanged(value);
    }
}

Q_INVOKABLE void TimePlot::setTimeFormat(const QString &format) const noexcept
{
    if(xAxis()) {
        const QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat(format);
        xAxis()->setTicker(timeTicker);
    }
}

Q_INVOKABLE void TimePlot::addCurrentTimeValue(const QString &name, const double value) const noexcept
{
    if(const auto graph = getGraph(name)) {
        graph->addData(m_currentTimeKey, value);
    }
}

Q_INVOKABLE void TimePlot::addCurrentTimeValues(QVariantMap values) const noexcept
{
    for(auto it = values.begin(); it != values.end(); ++it) {
        addCurrentTimeValue(it.key(), it.value().toDouble());
    }
}

void TimePlot::onTimeOut() noexcept
{
    auto todayString = QDateTime::currentDateTime().toString("yyyy-MM-dd") + " 00:00:00";
    auto todayTime = QDateTime::fromString(todayString, "yyyy-MM-dd hh:mm:ss");
    m_currentTimeKey = todayTime.msecsTo(QDateTime::currentDateTime()) / 1000.0;
    if(m_currentTimeKey - m_lastClearTime > m_plotTimeRangeInMilliseconds || m_currentTimeKey < m_lastClearTime) {
        auto map = graphsMap();
        std::for_each(map.begin(), map.end(), [this](auto graph) {
            if(graph) graph->removeDataBefore(m_currentTimeKey - m_plotTimeRangeInMilliseconds);
        });
        m_lastClearTime = m_currentTimeKey;
    }
    // if(m_currentTimeKey - m_lastAddedTime > 0.002 || m_currentTimeKey < m_lastAddedTime) {
    //     auto map = graphsMap();
    //     std::for_each(map.begin(), map.end(), [this](auto graph) {
    //         if(graph) graph->addData(m_currentTimeKey, 4.0);
    //     });
    //     m_lastAddedTime = m_currentTimeKey;
    // }
    if(xAxis())
        xAxis()->setRange(m_currentTimeKey - m_plotTimeRangeInMilliseconds, m_currentTimeKey);
    // QCP::MarginSide s = &static_cast<QCP::MarginSide*>((customPlot()->axisRect()->autoMargins()));
    // qDebug() << s;
}

void TimePlot::timerEvent(QTimerEvent *event)
{
    customPlot()->replot();
}

} // namespace QmlQCustomPlot