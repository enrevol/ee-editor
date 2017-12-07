#include <ciso646>

#include "scenetreeitem.hpp"
#include "scenetreemodel.hpp"

#include <parser/nodegraph.hpp>

namespace ee {
using Self = SceneTreeModel;

Self::SceneTreeModel(QObject* parent)
    : Super(parent) {}

Self::~SceneTreeModel() {}

void Self::setNodeGraph(const NodeGraph& graph) {
    rootItem_ = SceneTreeItem::createRootItem();
    auto node = SceneTreeItem::createChildItem(rootItem_.get());
    setupTree(node.get(), graph);
    rootItem_->addChild(std::move(node));
}

void Self::setupTree(SceneTreeItem* item, const NodeGraph& graph) {
    for (auto&& child : graph.getChildren()) {
        auto childItem = SceneTreeItem::createChildItem(item);
        setupTree(childItem.get(), child);
        item->addChild(std::move(childItem));
    }
}

SceneTreeItem* Self::getTreeItem(const QModelIndex& index) const {
    if (not index.isValid()) {
        return rootItem_.get();
    }
    return static_cast<SceneTreeItem*>(index.internalPointer());
}

QModelIndex Self::rootIndex() const {
    return index(0, 0, QModelIndex());
}

QVariant Self::data(const QModelIndex& index, int role) const {
    if (not index.isValid()) {
        return QVariant();
    }
    if (role != Qt::ItemDataRole::DisplayRole) {
        return QVariant();
    }
    auto item = getTreeItem(index);
    return item->data(index.column());
}

bool Self::setData(const QModelIndex& index, const QVariant& value, int role) {
    Q_UNUSED(index);
    Q_UNUSED(value);
    Q_UNUSED(role);
    return false;
}

QVariant Self::headerData(int section, Qt::Orientation orientation,
                          int role) const {
    if (orientation != Qt::Orientation::Horizontal) {
        return QVariant();
    }
    if (role != Qt::ItemDataRole::DisplayRole) {
        return QVariant();
    }
    return rootItem_->data(section);
}

QModelIndex Self::index(int row, int column, const QModelIndex& parent) const {
    if (not hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    auto parentItem = getTreeItem(parent);
    if (row > parentItem->childCount()) {
        return QModelIndex();
    }
    auto childItem = parentItem->child(row);
    Q_ASSERT(childItem != nullptr);
    return createIndex(row, column, childItem);
}

QModelIndex Self::parent(const QModelIndex& index) const {
    if (not index.isValid()) {
        return QModelIndex();
    }

    auto childItem = getTreeItem(index);
    auto parentItem = childItem->parent();
    if (parentItem == rootItem_.get()) {
        return QModelIndex();
    }
    return createIndex(parentItem->row(), 0, parentItem);
}

int Self::rowCount(const QModelIndex& parent) const {
    auto parentItem = getTreeItem(parent);
    return parentItem->childCount();
}

int Self::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 1;
}

Qt::ItemFlags Self::flags(const QModelIndex& index) const {
    QFlags<Qt::ItemFlag> flags;
    if (not index.isValid()) {
        return flags;
    }
    flags |= Qt::ItemFlag::ItemIsSelectable;
    flags |= Qt::ItemFlag::ItemIsEditable;
    flags |= Qt::ItemFlag::ItemIsDragEnabled;
    flags |= Qt::ItemFlag::ItemIsDropEnabled;
    flags |= Qt::ItemFlag::ItemIsEnabled;
    return flags;
}
} // namespace ee
