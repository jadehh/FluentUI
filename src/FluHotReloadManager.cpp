/**
# @File     : FluHotReloadManager.cpp
# @Author   : jade
# @Date     : 2025/8/25 21:55
# @Email    : jadehh@1ive.com
# @Software : Samples
# @Desc     : FluHotReloadManager.cpp
*/
#include "include/FluHotReloadManager.h"
#include <QQmlApplicationEngine>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <qqmlcomponent.h>
#include <QQuickWindow>
#include <QElapsedTimer>  // 添加这个头文件


class QQuickWindow;

FLuHotReloadManager::FLuHotReloadManager(QQmlApplicationEngine * engine, QUrl mainQmlPath, const char* name, const int major, const int minor, const char*singleQmlPath,const char* watchQmlPath, QObject* parent)
    : QObject(parent)
      , m_engine(engine)
      , m_watcher(new QFileSystemWatcher(this))
      , m_reloadDelay(100)
      , m_isWatching(false)
{
    m_mainQmlUrl = mainQmlPath;
    m_name = name;
    m_major = major;
    m_minor = minor;
    m_singleQmlPath = singleQmlPath;
    setWatchDirectory(watchQmlPath);
}

void FLuHotReloadManager::enableHotReloadManager()
{
    connect(m_watcher, &QFileSystemWatcher::fileChanged, this, &FLuHotReloadManager::onFileChanged);
    m_reloadTimer.setSingleShot(true);
    connect(&m_reloadTimer, &QTimer::timeout, this, &FLuHotReloadManager::performReload);
    setMainQmlUrl(m_mainQmlUrl);
    setReloadDelay(500); // 500ms延迟
}
FLuHotReloadManager::~FLuHotReloadManager()
{
    stopWatching();
}

void FLuHotReloadManager::setWatchDirectory(const QString& directory)
{
    if (m_watchDirectory != directory)
    {
        stopWatching();
        m_watchDirectory = directory;
    }
}


void FLuHotReloadManager::setMainQmlUrl(const QUrl& url)
{
    m_mainQmlUrl = url;
}


bool FLuHotReloadManager::startWatching()
{
    if (m_isWatching)
    {
        return true;
    }

    if (m_watchDirectory.isEmpty())
    {
        emit errorOccurred("Watch directory is not set");
        return false;
    }

    QDir dir(m_watchDirectory);
    if (!dir.exists())
    {
        emit errorOccurred("Directory does not exist: " + m_watchDirectory);
        return false;
    }

    try
    {
        watchDirectoryRecursively(m_watchDirectory);
        m_isWatching = true;
        qDebug() << "QML hot reload started. Watching" << m_watchedFiles.size() << "files";
        return true;
    }
    catch (const std::exception& e)
    {
        emit errorOccurred(QString("Failed to start watching: %1").arg(e.what()));
        return false;
    }
}

void FLuHotReloadManager::stopWatching()
{
    if (m_watcher && !m_watcher->files().isEmpty())
    {
        m_watcher->removePaths(m_watcher->files());
    }
    m_watchedFiles.clear();
    m_isWatching = false;
    m_reloadTimer.stop();
    qDebug() << "QML hot reload stopped";
}

void FLuHotReloadManager::setReloadDelay(int delayMs)
{
    m_reloadDelay = qMax(50, delayMs); // 最小延迟50ms
}

int FLuHotReloadManager::watchedFilesCount() const
{
    return m_watchedFiles.size();
}

bool FLuHotReloadManager::isWatching() const
{
    return m_isWatching;
}

void FLuHotReloadManager::watchDirectoryRecursively(const QString& path)
{
    QDir dir(path);
    if (!dir.exists())
    {
        return;
    }

    // 监视当前目录的所有QML文件
    QStringList filters;
    filters << "*.qml" << "*.QML";

    QStringList qmlFiles = dir.entryList(filters, QDir::Files);
    for (const QString& file : qmlFiles)
    {
        QString filePath = dir.absoluteFilePath(file);
        addFileToWatcher(filePath);
    }

    // 递归监视所有子目录
    QStringList subDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString& subDir : subDirs)
    {
        watchDirectoryRecursively(dir.absoluteFilePath(subDir));
    }
}

bool FLuHotReloadManager::addFileToWatcher(const QString& filePath)
{
    if (m_watchedFiles.contains(filePath))
    {
        return true;
    }

    if (m_watcher->addPath(filePath))
    {
        m_watchedFiles.insert(filePath);
        return true;
    }

    qWarning() << "Failed to watch file:" << filePath;
    return false;
}

void FLuHotReloadManager::removeFileFromWatcher(const QString& filePath)
{
    if (m_watchedFiles.contains(filePath))
    {
        m_watcher->removePath(filePath);
        m_watchedFiles.remove(filePath);
    }
}

void FLuHotReloadManager::onFileChanged(const QString& path)
{
    emit fileChanged(path);

    // 检查文件是否仍然存在（可能被删除）
    QFileInfo fileInfo(path);
    if (!fileInfo.exists())
    {
        removeFileFromWatcher(path);
        return;
    }

    // 重新添加监视（某些编辑器保存时会暂时移除文件）
    if (!m_watcher->files().contains(path))
    {
        addFileToWatcher(path);
    }

    // 启动或重置重载定时器
    if (!m_reloadTimer.isActive())
    {
        m_reloadTimer.start(m_reloadDelay);
    }
    else
    {
        m_reloadTimer.stop();
        m_reloadTimer.start(m_reloadDelay);
    }
}


void FLuHotReloadManager::registerQmlSingletonObject() const
{
    const QDir dir(m_singleQmlPath);
    if (!dir.exists())
    {
        return;
    }

    // 监视当前目录的所有QML文件
    QStringList filters;
    filters << "*.qml" << "*.QML";
    QFileInfoList  qmlFiles = dir.entryInfoList(filters, QDir::Files);
    for (const QFileInfo& file : qmlFiles)
    {
        QByteArray filePathArray = ("file:///" + file.absoluteFilePath()).toUtf8();
        QByteArray fileNameArray = file.baseName().toUtf8().constData();
        qmlRegisterSingletonType( QUrl(filePathArray.constData()), m_name, m_major, m_minor,fileNameArray.constData());
    }
}
void FLuHotReloadManager::performReload()
{
    emit reloadStarted();
    QMetaObject::invokeMethod(m_engine->rootObjects().first(), "restartApp"); // 重启程序
    m_engine->clearComponentCache();
    registerQmlSingletonObject();
    m_engine->load(m_mainQmlUrl);
    emit reloadCompleted();
}
