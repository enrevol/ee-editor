#ifndef EE_EDITOR_SCENE_TREE_HPP
#define EE_EDITOR_SCENE_TREE_HPP

#include <QTreeView>

namespace ee {
class NodeGraph;
class SelectionTree;
class Scene;
class Inspector;

class SceneTree : public QTreeView {
    Q_OBJECT

private:
    using Self = SceneTree;
    using Super = QTreeView;

public:
    explicit SceneTree(QWidget* parent = nullptr);

    virtual ~SceneTree() override;

    /// Gets the current node graph.
    virtual const NodeGraph& getNodeGraph() const = 0;

    /// Sets the node graph.
    /// @param graph The desired node graph.
    virtual void setNodeGraph(const NodeGraph& graph) = 0;

    /// Gets the currently selected nodes.
    virtual SelectionTree getCurrentSelection() const = 0;

    /// Manually selects nodes in the scene tree.
    virtual void selectTree(const SelectionTree& selectionTree) = 0;

Q_SIGNALS:
    /// Occurs when the user has selected new nodes.
    void selectionTreeChanged(const SelectionTree& selectionTree);
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_HPP
