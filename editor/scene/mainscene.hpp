#ifndef EE_EDITOR_MAIN_SCENE_HPP
#define EE_EDITOR_MAIN_SCENE_HPP

#include <QObject>

namespace ee {
class NodeGraph;
class SelectionTree;

class MainScene : public QObject {
    Q_OBJECT

public:
    MainScene();
    virtual ~MainScene() override;

    /// Sets the node graph.
    /// @param graph The desired node graph.
    virtual void setNodeGraph(const NodeGraph& graph) = 0;

    /// Sets the selection.
    /// @param selection The desired selection.
    virtual void selectTree(const SelectionTree& selection) = 0;

Q_SIGNALS:
    void selectionTreeChanged(const SelectionTree& selection);
};
} // namespace ee

#endif // EE_EDITOR_MAIN_SCENE_HPP
