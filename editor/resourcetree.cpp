#include "resourcetree.hpp"
#include "config.hpp"
#include "filesystemwatcher.hpp"

#include <QDebug>
#include <QHeaderView>

namespace ee {
namespace role {
constexpr auto full_file_path = 123456;
} // namespace role

using Self = ResourceTree;

Self ::ResourceTree(QWidget* parent)
    : Super(parent) {
    header()->close();

    auto&& watcher = FileSystemWatcher::getInstance();

    connect(&watcher, &FileSystemWatcher::fileChanged,
            [this](const QString& path) { updateResourceDirectories(); });

    connect(&watcher, &FileSystemWatcher::directoryChanged,
            [this](const QString& path) { updateResourceDirectories(); });

    connect(this, &Self::currentItemChanged, [this](QTreeWidgetItem* item) {
        if (item == nullptr) {
            // FIXME.
            return;
        }
        auto filePath = item->data(0, role::full_file_path).toString();
        qDebug() << "select item: " << filePath;
        fileSelected(filePath);
    });
}

void Self::setListenToFileChangeEvents(bool enabled) {
    listened_ = enabled;
    updateResourceDirectories();
}

void Self::updateResourceDirectories() {
    clear();
    if (listened_) {
        auto&& config = Config::getInstance();
        auto&& directories =
            config.getProjectSettings()->getResourceDirectories();

        for (const QDir& dir : directories) {
            auto item = new QTreeWidgetItem(this);
            updateResourcePath(item, QFileInfo(dir.absolutePath()));
        }
    }
}

void Self::updateResourcePath(QTreeWidgetItem* item, const QFileInfo& info) {
    item->setText(0, info.fileName());
    item->setData(0, role::full_file_path, info.absoluteFilePath());
    if (info.isDir()) {
        QDir dir(info.absoluteFilePath());
        for (const QFileInfo& entry : dir.entryInfoList(
                 QDir::Filter::NoDotAndDotDot | QDir::Filter::AllEntries)) {
            auto childItem = new QTreeWidgetItem(item);
            updateResourcePath(childItem, entry);
        }
    }
}
} // namespace ee
