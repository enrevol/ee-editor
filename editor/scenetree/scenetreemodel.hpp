#ifndef EE_EDITOR_SCENE_TREE_MODEL_HPP
#define EE_EDITOR_SCENE_TREE_MODEL_HPP

#include <memory>

#include <QAbstractItemModel>

namespace ee {
class NodeGraph;
class SceneTreeItem;

class SceneTreeModel : public QAbstractItemModel {
private:
    using Self = SceneTreeModel;
    using Super = QAbstractItemModel;

public:
    /// Constructs a scene tree model.
    explicit SceneTreeModel(QObject* parent = nullptr);

    virtual ~SceneTreeModel() override;

    /// Sets the node graph reference.
    void setNodeGraph(NodeGraph& graph);

    QModelIndex rootIndex() const;

    /// @see Super.
    virtual QVariant data(const QModelIndex& index, int role) const override;

    /// @see Super.
    virtual bool setData(const QModelIndex& index, const QVariant& value,
                         int role) override;

    /// @see Super.
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role) const override;

    /// @see Super.
    virtual QModelIndex
    index(int row, int column,
          const QModelIndex& parent = QModelIndex()) const override;

    /// @see Super.
    virtual QModelIndex parent(const QModelIndex& index) const override;

    /// @see Super.
    virtual int
    rowCount(const QModelIndex& parent = QModelIndex()) const override;

    /// @see Super.
    virtual int
    columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /// @see Super.
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

protected:
    /// Constructs the scene tree item with the corresponding node graph.
    void setupTree(SceneTreeItem* item, const NodeGraph& graph);

    /// Gets the tree item for the specified model index.
    SceneTreeItem* getTreeItem(const QModelIndex& index) const;

private:
    /// Reference to the node graph.
    NodeGraph* nodeGraph_;

    /// Root scene tree item.
    std::unique_ptr<SceneTreeItem> rootItem_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_MODEL_HPP
