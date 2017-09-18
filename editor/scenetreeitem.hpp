#ifndef EE_EDITOR_SCENE_TREE_ITEM_HPP
#define EE_EDITOR_SCENE_TREE_ITEM_HPP

#include <QList>
#include <QPointer>

namespace ee {
class NodeGraph;

class SceneTreeItem {
private:
    using Self = SceneTreeItem;

public:
    explicit SceneTreeItem(Self* parent = nullptr);

    ~SceneTreeItem();

    Self* parent();
    const Self* parent() const;

    Self* child(int row);
    const Self* child(int row) const;

    void appendChild(std::unique_ptr<Self> child);

    int columnCount() const;
    QVariant data(int column) const;

    int childCount() const;
    int row() const;

private:
    std::vector<std::unique_ptr<Self>> children_;
    Self* parent_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_ITEM_HPP
