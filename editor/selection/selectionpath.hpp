#ifndef EE_EDITOR_SELECTION_PATH_HPP
#define EE_EDITOR_SELECTION_PATH_HPP

#include <QModelIndex>
#include <QVector>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeGraph;
class SceneTreeModel;

/// Represents a selection path.
class SelectionPath {
private:
    using Self = SelectionPath;

public:
    /// Creats an empty selection.
    static Self emptySelection();

    /// Creates a selection that selects the root node.
    static Self selectRoot();

    /// Creates a selection with the selected indices.
    static Self select(const QVector<int>& indices);

    /// Creates a selection from specified model index.
    static Self fromIndex(const QModelIndex& index,
                          const QModelIndex& ancestor = QModelIndex());

    /// Creates a selection from the specified node and its ancestor.
    static Self fromNode(const cocos2d::Node* node,
                         const cocos2d::Node* ancestor);

    /// Checks whether this selection is empty.
    bool isEmpty() const;

    /// Checks whether this selection selects the root node.
    bool isRoot() const;

    /// Gets the selected indices.
    const QVector<int>& getIndices() const;

    bool isSibling(const Self& other) const;

    QModelIndex find(const SceneTreeModel& model) const;

    /// Finds the node.
    cocos2d::Node* find(cocos2d::Node* node) const;

    /// Finds the node (const version).
    const cocos2d::Node* find(const cocos2d::Node* node) const;

    /// Finds the node graph.
    NodeGraph& find(NodeGraph& graph) const;

    /// Finds the node graph (const version).
    const NodeGraph& find(const NodeGraph& graph) const;

    bool operator==(const Self& other) const;

protected:
    explicit SelectionPath(bool root, const QVector<int>& indices);

private:
    bool root_;
    QVector<int> indices_;
};
} // namespace ee

#endif // EE_EDITOR_SELECTION_PATH_HPP
