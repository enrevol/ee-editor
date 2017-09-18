#include "scenetreeitem.hpp"

namespace ee {
using Self = SceneTreeItem;

Self::SceneTreeItem(Self* parent)
    : parent_(parent) {}

Self::~SceneTreeItem() {}

Self* Self::parent() {
    return parent_;
}

const Self* Self::parent() const {
    return parent_;
}

Self* Self::child(int row) {
    if (static_cast<std::size_t>(row) > children_.size()) {
        return nullptr;
    }
    return children_.at(static_cast<std::size_t>(row)).get();
}

const Self* Self::child(int row) const {
    return static_cast<const Self*>(const_cast<Self*>(this)->child(row));
}

void Self::appendChild(std::unique_ptr<Self> child) {
    children_.push_back(std::move(child));
}

int Self::columnCount() const {
    return 1;
}

QVariant Self::data(int column) const {
    return "_Node";
}

int Self::childCount() const {
    return static_cast<int>(children_.size());
}

int Self::row() const {
    if (parent() == nullptr) {
        return 0;
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
