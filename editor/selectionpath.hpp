#ifndef EE_EDITOR_SELECTION_PATH_HPP
#define EE_EDITOR_SELECTION_PATH_HPP

#include <QModelIndex>
#include <QVector>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeGraph;

class SelectionPath {
private:
    using Self = SelectionPath;

public:
    static Self emptySelection();
    static Self selectRoot();
    static Self select(const QVector<int>& indices);
    static Self fromIndex(const QModelIndex& index,
                          const QModelIndex& ancestor = QModelIndex());

    bool isEmpty() const;
    bool isRoot() const;
    const QVector<int>& getIndices() const;

    bool isSibling(const Self& other) const;

    /// Finds the node.
    cocos2d::Node* find(cocos2d::Node* node) const;

    /// Finds the node (const version).
    const cocos2d::Node* find(const cocos2d::Node* node) const;

    /// Finds the node graph.
    NodeGraph& find(NodeGraph& graph) const;

    /// Finds the node graph (const version).
    const NodeGraph& find(const NodeGraph& graph) const;

protected:
    explicit SelectionPath(bool root, const QVector<int>& indices);

private:
    bool root_;
    QVector<int> indices_;
};
} // namespace ee

#endif // EE_EDITOR_SELECTION_PATH_HPP
