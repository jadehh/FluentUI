/**
# @File     : FluHotReloadManager.h.h
# @Author   : jade
# @Date     : 2025/8/25 21:55
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluHotReloadManager.h
*/
#pragma once

#include <QApplication>
#include <QObject>
#include <QFileSystemWatcher>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QSet>
#include <QTimer>
#include <QUrl>

class FLuHotReloadManager : public QObject
{
    Q_OBJECT

public:


    explicit FLuHotReloadManager(QQmlApplicationEngine *engine, QUrl mainQmlPath, const char* name,int major,int minor,const char* singleQmlPath, const char* watchQmlPath, QObject *parent = nullptr);
    ~FLuHotReloadManager() override;

    // 是否启用监听
    void enableHotReloadManager();

    // 设置监视的根目录
    void setWatchDirectory(const QString &directory);

    // 开始监视
    bool startWatching();

    // 停止监视
    void stopWatching();

    // 设置重载延迟时间（毫秒）
    void setReloadDelay(int delayMs);

    // 获取当前监视的文件数量
    int watchedFilesCount() const;

    // 是否正在监视
    bool isWatching() const;

    // 新增设置主QML路径的方法
    void setMainQmlUrl(const QUrl& url);

    void registerQmlSingletonObject() const;



    signals:
        void fileChanged(const QString &filePath);
    void reloadStarted();
    void reloadCompleted();
    void errorOccurred(const QString &errorMessage);



private slots:
    void onFileChanged(const QString &path);
    void performReload();

private:
    // 递归监视目录
    void watchDirectoryRecursively(const QString &path);

    // 添加文件到监视器
    bool addFileToWatcher(const QString &filePath);

    // 移除文件从监视器
    void removeFileFromWatcher(const QString &filePath);

private:
    QUrl m_mainQmlUrl;
    const char* m_singleQmlPath;
    const char* m_name;
    int m_major;
    int m_minor;
    QObject* m_rootObject = nullptr;
    QQmlApplicationEngine *m_engine;
    QFileSystemWatcher *m_watcher;
    QSet<QString> m_watchedFiles;
    QTimer m_reloadTimer;
    QString m_watchDirectory;
    int m_reloadDelay;
    bool m_isWatching;
};


