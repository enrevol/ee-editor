#ifndef EE_EDITOR_FILE_SYSTEM_WATCHER_HPP
#define EE_EDITOR_FILE_SYSTEM_WATCHER_HPP

#include <QDir>
#include <QFileSystemWatcher>
#include <QVector>

namespace ee {
class FileSystemWatcher : public QObject {
    Q_OBJECT

private:
    using Self = FileSystemWatcher;

public:
    static Self& getInstance();

    void setDirectories(const QVector<QDir>& directories);

Q_SIGNALS:
    void fileChanged(const QString& path);
    void directoryChanged(const QString& path);

private:
    FileSystemWatcher();
    ~FileSystemWatcher();

    FileSystemWatcher(const Self&) = delete;
    Self& operator=(const Self&) = delete;

    QVector<QDir> directories_;
    QFileSystemWatcher watcher_;
};
} // namespace ee

#endif // EE_EDITOR_FILE_SYSTEM_WATCHER_HPP
