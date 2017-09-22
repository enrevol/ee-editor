#ifndef EE_EDITOR_SCENE_TREE_HPP
#define EE_EDITOR_SCENE_TREE_HPP

#include <QTreeView>

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeGraph;
class SceneTreeModel;
class SelectionPath;
class SelectionTree;

/// Display the scene tree nodes.
class SceneTree : public QTreeView {
    Q_OBJECT

private:
    using Self = SceneTree;
    using Super = QTreeView;

public:
    explicit SceneTree(QWidget* parent);

    virtual ~SceneTree() override;

    const NodeGraph& getNodeGraph() const;

    /// Sets the node graph.
    void setNodeGraph(const NodeGraph& graph);

    /// Gets the currently selected nodes.
    SelectionTree currentSelection() const;

    /// Updates the property for the selection.
    /// @param path The selection path.
    /// @param propertyName The name of the property.
    /// @param value The value of the property.
    void updateSelectionProperty(const SelectionPath& path,
                                 const QString& propertyName,
                                 const cocos2d::Value& value);

Q_SIGNALS:
    void sceneSelectionChanged(const SelectionTree& selection);

protected:
    virtual void selectionChanged(const QItemSelection& selected,
                                  const QItemSelection& deselected) override;

private:
    std::unique_ptr<NodeGraph> nodeGraph_;
    std::unique_ptr<SceneTreeModel> treeModel_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_HPP
