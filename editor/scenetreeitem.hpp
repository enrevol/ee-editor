#ifndef EE_EDITOR_SCENE_TREE_ITEM_HPP
#define EE_EDITOR_SCENE_TREE_ITEM_HPP

#include <memory>

#include <QVariant>

namespace ee {
class NodeGraph;

class SceneTreeItem {
private:
    using Self = SceneTreeItem;

public:
    static std::unique_ptr<Self> createRootItem();
    static std::unique_ptr<Self> createChildItem(Self* parent);

    ~SceneTreeItem();

    bool isRoot() const;

    /// Gets the parent of this item.
    /// @return The parent if exist, nullptr if root.
    Self* parent();

    /// Gets the parent of this item (const version).
    const Self* parent() const;

    /// Gets the child of this item.
    /// @param row The row of the child item.
    Self* child(int row);

    /// Gets the child of this item (const version).
    const Self* child(int row) const;

    /// Adds the specified child to this item.
    void addChild(std::unique_ptr<Self> child);

    int columnCount() const;
    QVariant data(int column) const;

    int childCount() const;

    /// Gets the row index of this item in its parent.
    /// @return -1 if this item is root.
    int row() const;

protected:
    /// Constructs a scene tree item.
    /// @param parent The parent of this item.
    explicit SceneTreeItem(Self* parent = nullptr);

private:
    std::vector<std::unique_ptr<Self>> children_;
    Self* parent_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_ITEM_HPP
