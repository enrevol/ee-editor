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

class SceneTree : public QTreeView {
    Q_OBJECT

private:
    using Self = SceneTree;
    using Super = QTreeView;

public:
    explicit SceneTree(QWidget* parent);

    void setNodeGraph(const NodeGraph& graph);

protected:
private:
    SceneTreeModel* treeModel_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_HPP
