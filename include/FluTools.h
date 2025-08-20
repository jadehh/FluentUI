/**
# @File     : FluTools.h
# @Author   : jade
# @Date     : 2025/8/18 19:43
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluTools.h
*/
//

#ifndef FLUTOOLS_H
#define FLUTOOLS_H
#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <QQuickWindow>
#include "singleton.h"

/**
 * @brief The FluTools class
 */
class FluTools final : public QObject {
    Q_OBJECT
    QML_NAMED_ELEMENT(FluTools)
    QML_SINGLETON

private:
    explicit FluTools(QObject *parent = nullptr);

public:
    SINGLETON(FluTools)

    static FluTools *create(QQmlEngine *, QJSEngine *) {
        return getInstance();
    }

    Q_INVOKABLE static int qtMajor();

    Q_INVOKABLE static int qtMinor();

    Q_INVOKABLE static bool isMacos();

    Q_INVOKABLE static bool isLinux();

    Q_INVOKABLE static bool isWin();

    Q_INVOKABLE static void clipText(const QString &text);

    Q_INVOKABLE static QString uuid();

    Q_INVOKABLE static QString readFile(const QString &fileName);

    Q_INVOKABLE static void setQuitOnLastWindowClosed(bool val);

    Q_INVOKABLE static void setOverrideCursor(Qt::CursorShape shape);

    Q_INVOKABLE static void restoreOverrideCursor();

    Q_INVOKABLE static QString html2PlantText(const QString &html);

    Q_INVOKABLE static QString toLocalPath(const QUrl &url);

    Q_INVOKABLE static void deleteLater(QObject *p);

    Q_INVOKABLE static QString getFileNameByUrl(const QUrl &url);

    Q_INVOKABLE static QRect getVirtualGeometry();

    Q_INVOKABLE static QString getApplicationDirPath();

    Q_INVOKABLE static QUrl getUrlByFilePath(const QString &path);

    Q_INVOKABLE static QColor withOpacity(const QColor &, qreal alpha);

    Q_INVOKABLE static QString md5(const QString &text);

    Q_INVOKABLE static QString sha256(const QString &text);

    Q_INVOKABLE static QString toBase64(const QString &text);

    Q_INVOKABLE static QString fromBase64(const QString &text);

    Q_INVOKABLE static bool removeDir(const QString &dirPath);

    Q_INVOKABLE static bool removeFile(const QString &filePath);

    Q_INVOKABLE static void showFileInFolder(const QString &path);

    Q_INVOKABLE static bool isSoftware();

    Q_INVOKABLE static qint64 currentTimestamp();

    Q_INVOKABLE static QPoint cursorPos();

    Q_INVOKABLE static QIcon windowIcon();

    Q_INVOKABLE static int cursorScreenIndex();

    Q_INVOKABLE static int windowBuildNumber();

    Q_INVOKABLE static bool isWindows11OrGreater();

    Q_INVOKABLE static bool isWindows10OrGreater();

    Q_INVOKABLE static QRect desktopAvailableGeometry(QQuickWindow *window);

    Q_INVOKABLE static QString getWallpaperFilePath();

    Q_INVOKABLE static QColor imageMainColor(const QImage &image, double bright = 1);
};

#endif //FLUTOOLS_H
