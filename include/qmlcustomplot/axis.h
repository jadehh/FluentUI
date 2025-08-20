/**
# @File     : axis.h
# @Author   : jade
# @Date     : 2025/8/18 17:31
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : axis.h
*/
//

#ifndef AXIS_H
#define AXIS_H
#include <QtCore/QObject>
#include <QtQml/qqml.h>
#include "include/qmlcustomplot/grid.h"
#include "include/qmlcustomplot/ticker.h"
#include "include/qmlcustomplot/macros.h"

class QCPAxis;
class QCPAxisTicker;
class QCustomPlot;


namespace QmlQCustomPlot
{

    class Grid;
    class Ticker;
    class Axis : public QObject
    {
        Q_OBJECT
        QML_READ_WRITE_NOTIFY_PROPERTY(bool , visible)
        QML_READ_WRITE_NOTIFY_PROPERTY(QString , label)
        QML_READ_WRITE_NOTIFY_PROPERTY(float , upper)
        QML_READ_WRITE_NOTIFY_PROPERTY(float , lower)
        QML_READ_CONSTANT(QmlQCustomPlot::Grid*,  grid)
        QML_READ_CONSTANT(QmlQCustomPlot::Ticker*,  ticker)
        QML_ELEMENT
        QML_UNCREATABLE("")
    public:
        explicit Axis(QObject *parent = nullptr);
        Axis(QCPAxis* axis, QCustomPlot *parentPlot, QObject *parent = nullptr);
        ~Axis() override;

        Q_ENUMS(TickerType)
        enum TickerType { Fixed, Log, Pi, Text, DateTime, Time };
        Q_INVOKABLE void setTickerType(TickerType type) const;
        Q_INVOKABLE void setRange(float position, float size, Qt::AlignmentFlag align) const noexcept;
        Q_INVOKABLE void setRange(float lower, float upper) const noexcept;

        void setTicker(const QSharedPointer<QCPAxisTicker>& ticker) const noexcept;

        void set_visible(bool value) noexcept;
        void set_label(const QString &value) noexcept;
        void set_upper(float value) noexcept;
        void set_lower(float value) noexcept;

    private:
        void updateProperty() noexcept;

    private:
        QCustomPlot *m_parentPlot = nullptr;
        QCPAxis* m_axis = nullptr;
    };

} // namespace QmlQCustomPlot

#endif //AXIS_H
