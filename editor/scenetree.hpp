#ifndef EE_EDITOR_SCENE_TREE_HPP
#define EE_EDITOR_SCENE_TREE_HPP

#include <QTreeWidget>

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeGraph;

class SceneTree : public QTreeWidget {
    Q_OBJECT

private:
    using Self = SceneTree;
    using Super = QTreeWidget;

public:
    explicit SceneTree(QWidget* parent);

    void setNodeGraph(const NodeGraph& graph);

protected:
    void updateNode(QTreeWidgetItem* item, const NodeGraph& graph);

private:
    QTreeWidgetItem* rootItem_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_HPP
