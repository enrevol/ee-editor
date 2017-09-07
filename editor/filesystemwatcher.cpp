#include "filesystemwatcher.hpp"

#include <QDebug>

namespace ee {
using Self = FileSystemWatcher;

Self& Self::getInstance() {
    static Self sharedInstance;
    return sharedInstance;
}

Self::FileSystemWatcher() {
    connect(&watcher_, &QFileSystemWatcher::fileChanged,
            [this](const QString& path) {
                qInfo() << "file changed: " << path;
                fileChanged(path);
            });

    connect(&watcher_, &QFileSystemWatcher::directoryChanged,
            [this](const QString& path) {
                qInfo() << "directory changed: " << path;
                directoryChanged(path);
            });
}

Self::~FileSystemWatcher() {}

void Self::setDirectories(const QVector<QDir>& directories) {
    for (const QDir& dir : directories_) {
        watcher_.removePath(dir.absolutePath());
    }
    for (const QDir& dir : directories) {
        watcher_.addPath(dir.absolutePath());
    }
    directories_ = directories;
}
} // namespace ee
