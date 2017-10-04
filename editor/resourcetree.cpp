#include <ciso646>

#include "config.hpp"
#include "fileclassifier.hpp"
#include "filesystemwatcher.hpp"
#include "resourcetree.hpp"
#include "spritesheet.hpp"

#include <2d/CCSpriteFrameCache.h>
#include <platform/CCFileUtils.h>

#include <QDebug>
#include <QHeaderView>
#include <QMimeData>
#include <QStack>

namespace ee {
namespace role {
constexpr auto full_file_path = 123456;

} // namespace role

namespace {
void setFullFilePath(QTreeWidgetItem* item, const QString& path) {
    item->setData(0, role::full_file_path, path);
}

QString getFullFilePath(const QTreeWidgetItem* item) {
    return item->data(0, role::full_file_path).toString();
}
} // namespace

using Self = ResourceTree;

Self::ResourceTree(QWidget* parent)
    : Super(parent) {
    header()->close();
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragDropMode::DragOnly);

    connect(this, &Self::currentItemChanged, [this](QTreeWidgetItem* item) {
        if (item == nullptr) {
            // FIXME.
            return;
        }
        auto filePath = getFullFilePath(item);
        qDebug() << "select item: " << filePath;
        FileClassifier classifier(filePath);
        Q_EMIT noneSelected();
        if (classifier.isImage()) {
            Q_EMIT imageSelected(filePath);
            return;
        }
        auto parent = item->parent();
        if (parent != nullptr) {
            auto parentPath = getFullFilePath(parent);
            if (FileClassifier(parentPath).isSpriteSheet()) {
                Q_EMIT spriteFrameSelected(item->text(0));
                return;
            }
        }
    });

    connect(this, &Self::itemDoubleClicked,
            [this](QTreeWidgetItem* item, int column) {
                Q_UNUSED(column);
                auto filePath = getFullFilePath(item);
                QFileInfo fileInfo(filePath);
                FileClassifier classifier(filePath);
                if (classifier.isInterface()) {
                    Q_EMIT interfaceSelected(filePath);
                }
            });
}

void Self::setListenToFileChangeEvents(bool enabled) {
    listened_ = enabled;
    updateResourceDirectories();
}

void Self::updateResourceDirectories() {
    if (not listened_) {
        clear();
        return;
    }

    auto expandedItems = saveExpandedItems();
    auto selectedItem = saveSelectedItem();
    reloadResources();
    restoreExpandedItems(expandedItems);
    restoreSelectedItem(selectedItem);
}

void Self::updateResourcePath(QTreeWidgetItem* item, const QFileInfo& info) {
    item->setText(0, info.fileName());
    auto fullPath = info.absoluteFilePath();
    setFullFilePath(item, fullPath);
    if (info.isDir()) {
        QDir dir(info.absoluteFilePath());
        for (const QFileInfo& entry : dir.entryInfoList(
                 QDir::Filter::NoDotAndDotDot | QDir::Filter::AllEntries)) {
            auto childItem = new QTreeWidgetItem(item);
            updateResourcePath(childItem, entry);
        }
    } else {
        FileClassifier classifier(fullPath);
        if (classifier.isSpriteSheet()) {
            auto path = getPath(item);
            auto fileUtils = cocos2d::FileUtils::getInstance();
            auto content = fileUtils->getStringFromFile(path.toStdString());
            SpriteSheet sheet(QString::fromStdString(content));
            for (auto&& frame : sheet.getFrames()) {
                auto childItem = new QTreeWidgetItem(item);
                childItem->setText(0, frame);
            }
        }
    }
}

QSet<QString> Self::saveExpandedItems() {
    QSet<QString> expandedItems;
    for (QTreeWidgetItemIterator iter(this); *iter != nullptr; ++iter) {
        auto&& item = *iter;
        if (isItemExpanded(item)) {
            auto filePath = getFullFilePath(item);
            expandedItems.insert(filePath);
        }
    }
    return expandedItems;
}

void Self::restoreExpandedItems(const QSet<QString>& expandedItems) {
    for (QTreeWidgetItemIterator iter(this); *iter != nullptr; ++iter) {
        auto&& item = *iter;
        auto filePath = item->data(0, role::full_file_path).toString();
        if (expandedItems.contains(filePath)) {
            expandItem(item);
        }
    }
}

void Self::reloadResources() {
    clear();
    auto&& config = Config::getInstance();
    auto&& directories = config.getProjectSettings().getResourceDirectories();

    for (const QDir& dir : directories) {
        auto item = new QTreeWidgetItem(this);
        updateResourcePath(item, QFileInfo(dir.absolutePath()));
    }
}

QStack<QString> Self::saveSelectedItem() {
    QStack<QString> indices;
    if (currentItem() != nullptr) {
        auto item = currentItem();
        while (item->parent() != nullptr) {
            indices.append(item->data(0, role::full_file_path).toString());
            item = item->parent();
        }
        indices.append(item->data(0, role::full_file_path).toString());
    }
    return indices;
}

void Self::restoreSelectedItem(QStack<QString> names) {
    if (names.empty()) {
        return;
    }

    QTreeWidgetItem* currentItem = nullptr;
    auto oldTopName = names.pop();
    for (int i = 0; i < topLevelItemCount(); ++i) {
        auto item = topLevelItem(i);
        if (currentItem != nullptr &&
            item->data(0, role::full_file_path).toString() > oldTopName) {
            break;
        }
        currentItem = item;
    }
    if (currentItem == nullptr) {
        return;
    }

    while (not names.empty()) {
        QTreeWidgetItem* nextItem = nullptr;
        auto oldName = names.pop();
        for (int i = 0; i < currentItem->childCount(); ++i) {
            auto item = currentItem->child(i);
            if (nextItem != nullptr &&
                item->data(0, role::full_file_path).toString() > oldName) {
                break;
            }
            nextItem = item;
        }
        if (nextItem == nullptr) {
            break;
        }
        currentItem = nextItem;
    }

    setCurrentItem(currentItem);
}

QStringList Self::getPathComponents(const QTreeWidgetItem* item) const {
    QStringList components;
    while (item->parent() != nullptr) {
        components << item->text(0);
        item = item->parent();
    }
    std::reverse(components.begin(), components.end());
    return components;
}

QString Self::getPath(const QTreeWidgetItem* item) const {
    auto components = getPathComponents(item);
    return components.join(QDir ::separator());
}

QMimeData* Self::mimeData(const QList<QTreeWidgetItem*> items) const {
    Q_ASSERT(items.size() > 0);
    auto item = items.front();
    auto path = getPath(item);
    auto data = new QMimeData();
    data->setData(mimeTypes().at(0), path.toUtf8());
    return data;
}

QStringList Self::mimeTypes() const {
    QStringList types;
    types << "ee-editor/resources–path";
    return types;
}
} // namespace ee
