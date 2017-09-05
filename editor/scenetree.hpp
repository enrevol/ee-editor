#ifndef EE_EDITOR_SCENE_TREE_HPP
#define EE_EDITOR_SCENE_TREE_HPP

#include <QTreeWidget>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class SceneTree : public QTreeWidget {
    Q_OBJECT

private:
    using Self = SceneTree;
    using Super = QTreeWidget;

public:
    explicit SceneTree(QWidget* parent);

    void setRootNode(cocos2d::Node* node);

protected:
private:
    cocos2d::Node* rootNode_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_HPP
