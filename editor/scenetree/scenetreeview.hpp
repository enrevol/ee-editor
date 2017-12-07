#ifndef EE_EDITOR_SCENE_TREE_VIEW_HPP
#define EE_EDITOR_SCENE_TREE_VIEW_HPP

#include "scenetree/scenetree.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class Value;
class SceneTreeModel;
class SelectionPath;
class SelectionTree;

/// Display the scene tree nodes.
class SceneTreeView : public SceneTree {
    using Self = SceneTreeView;
    using Super = SceneTree;

public:
    explicit SceneTreeView(QWidget* parent);

    virtual ~SceneTreeView() override;

    /// @see Super.
    virtual const NodeGraph& getNodeGraph() const override;

    /// @see Super.
    virtual void setNodeGraph(const NodeGraph& graph) override;

    /// @see Super.
    virtual SelectionTree getCurrentSelection() const override;

    /// @see Super.
    virtual void selectTree(const SelectionTree& selectionTree) override;

protected:
    virtual void selectionChanged(const QItemSelection& selected,
                                  const QItemSelection& deselected) override;

private:
    bool selecting_;
    std::unique_ptr<NodeGraph> nodeGraph_;
    std::unique_ptr<SceneTreeModel> treeModel_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_VIEW_HPP
