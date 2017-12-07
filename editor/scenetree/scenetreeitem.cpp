#include "scenetreeitem.hpp"

namespace ee {
using Self = SceneTreeItem;

std::unique_ptr<Self> Self::createRootItem() {
    return std::unique_ptr<Self>(new Self(nullptr));
}

std::unique_ptr<Self> Self::createChildItem(Self* parent) {
    return std::unique_ptr<Self>(new Self(parent));
}

Self::SceneTreeItem(Self* parent)
    : parent_(parent) {}

Self::~SceneTreeItem() {}

bool Self::isRoot() const {
    return parent() == nullptr;
}

Self* Self::parent() {
    return parent_;
}

const Self* Self::parent() const {
    return parent_;
}

Self* Self::child(int row_) {
    auto row = static_cast<std::size_t>(row_);
    if (row > children_.size()) {
        return nullptr;
    }
    return children_.at(row).get();
}

const Self* Self::child(int row) const {
    return static_cast<const Self*>(const_cast<Self*>(this)->child(row));
}

void Self::addChild(std::unique_ptr<Self> child) {
    children_.push_back(std::move(child));
}

int Self::columnCount() const {
    return 1;
}

QVariant Self::data(int column) const {
    Q_UNUSED(column);
    return "_Node";
}

int Self::childCount() const {
    return static_cast<int>(children_.size());
}

int Self::row() const {
    if (isRoot()) {
        return -1;
    }
    for (int i = 0; i < parent()->childCount(); ++i) {
        if (parent()->child(i) == this) {
            return i;
        }
    }
    Q_ASSERT(false);
    return -1;
}
} // namespace ee
