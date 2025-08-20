/**
# @File     : axis.cpp
# @Author   : jade
# @Date     : 2025/8/18 17:31
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : axis.cpp
*/
//
#include "include/qmlcustomplot/axis.h"
#include "include/qmlcustomplot/grid.h"
#include "include/qmlcustomplot/ticker.h"
#include "include/qmlcustomplot/qcustomplot.h"

#include <stdexcept>

namespace QmlQCustomPlot
{

Axis::Axis(QObject *parent) :  QObject(parent)
{

}


Axis::Axis(QCPAxis* axis, QCustomPlot *parentPlot, QObject *parent)
    :  QObject(parent), m_parentPlot(parentPlot), m_axis(axis)
{
    if(parentPlot == nullptr || axis == nullptr)
        throw std::invalid_argument(nullptr);
    connect(parentPlot, &QCustomPlot::beforeReplot, this, &Axis::updateProperty);
    connect(axis, &QCPAxis::destroyed, this, &Axis::deleteLater);
    m_ticker = new Ticker(axis, m_parentPlot, this);
    m_grid = new Grid(axis->grid(), m_parentPlot, this);
    updateProperty();
}

Axis::~Axis()
{

}

void Axis::setTickerType(const TickerType type) const
{
    QSharedPointer<QCPAxisTicker> ticker;
    switch (type)
    {
    default:
    case Fixed:
        ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerFixed);
        break;
    case Log:
        ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerLog);
        break;
    case Pi:
        ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerPi);
        break;
    case Text:
        ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerText);
        break;
    case DateTime:
        ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerDateTime);
        break;
    case Time:
        ticker = QSharedPointer<QCPAxisTicker>(new QCPAxisTickerTime);
        break;
    }
    m_axis->setTicker(ticker);
    m_parentPlot->replot();
}

void Axis::setRange(const float position, const float size, const Qt::AlignmentFlag align) const noexcept
{
    m_axis->setRange(position, size, align);
    m_parentPlot->replot();
}

Q_INVOKABLE void Axis::setRange(const float lower, const float upper) const noexcept
{
    m_axis->setRange(lower, upper);
}

void Axis::setTicker(const QSharedPointer<QCPAxisTicker>& ticker) const noexcept
{
    m_axis->setTicker(ticker);
    m_parentPlot->replot();
}

void Axis::set_visible(const bool value) noexcept
{
    m_visible = m_axis->visible();
    if(m_visible == value) return;
    m_visible = value;
    m_axis->setVisible(value);
    Q_EMIT visibleChanged(m_visible);
    m_parentPlot->replot();
}

void Axis::set_label(const QString &value) noexcept
{
    m_label = m_axis->label();
    if(m_label == value) return;
    m_label = value;
    m_axis->setLabel(value);
    Q_EMIT labelChanged(m_label);
    m_parentPlot->replot();
}

void Axis::set_upper(const float value) noexcept
{
    m_upper = m_axis->range().upper;
    if(m_upper == value) return;
    m_upper = value;
    m_axis->setRangeLower(value);
    Q_EMIT upperChanged(m_upper);
    m_parentPlot->replot();
}

void Axis::set_lower(const float value) noexcept
{
    m_lower = m_axis->range().lower;
    if(m_lower == value) return;
    m_lower = value;
    m_axis->setRangeUpper(value);
    Q_EMIT lowerChanged(m_lower);
    m_parentPlot->replot();
}

void Axis::updateProperty() noexcept
{
    m_visible = m_axis->visible();
    m_label = m_axis->label();
    m_upper = m_axis->range().upper;
    m_lower = m_axis->range().lower;
    Q_EMIT visibleChanged(m_visible);
    Q_EMIT labelChanged(m_label);
    Q_EMIT upperChanged(m_upper);
    Q_EMIT lowerChanged(m_lower);
}

} // namespace QmlQCustomPlot
