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
class SceneSelection;

class SceneTree : public QTreeView {
    Q_OBJECT

private:
    using Self = SceneTree;
    using Super = QTreeView;

public:
    explicit SceneTree(QWidget* parent);

    virtual ~SceneTree() override;

    const NodeGraph& getNodeGraph() const;

    void setNodeGraph(const NodeGraph& graph);

    SceneSelection currentSelection() const;

Q_SIGNALS:
    void selectionChanged(const SceneSelection& selection);

protected:
    virtual void selectionChanged(const QItemSelection& selected,
                                  const QItemSelection& deselected) override;

private:
    std::unique_ptr<NodeGraph> nodeGraph_;
    std::unique_ptr<SceneTreeModel> treeModel_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_HPP
