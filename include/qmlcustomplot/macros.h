/**
# @File     : macros.h
# @Author   : jade
# @Date     : 2025/8/18 17:35
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : macros.h
*/
//

#ifndef MACROS_H
#define MACROS_H

namespace QmlQCustomPlot
{
#define QML_READ_WRITE_NOTIFY_PROPERTY(TYPE, NAME) \
Q_PROPERTY(TYPE NAME READ NAME WRITE set_##NAME NOTIFY NAME##Changed) \
public: \
TYPE NAME() const { return m_##NAME; } \
Q_SIGNAL void NAME##Changed(TYPE); \
private: \
TYPE m_##NAME {};

#define QML_READ_NOTIFY_PROPERTY(TYPE, NAME) \
Q_PROPERTY(TYPE NAME READ NAME NOTIFY NAME##Changed) \
public: \
TYPE NAME() const { return m_##NAME; } \
Q_SIGNAL void NAME##Changed(TYPE); \
private: \
TYPE m_##NAME {};

#define QML_READ_CONSTANT(TYPE, NAME) \
Q_PROPERTY(TYPE NAME READ NAME CONSTANT) \
public: \
TYPE NAME() const { return m_##NAME; } \
Q_SIGNAL void NAME##Changed(TYPE); \
private: \
TYPE m_##NAME {};
} // namespace QmlQCustomPlot
#endif //MACROS_H
