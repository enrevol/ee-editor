#ifndef EE_EDITOR_SCENE_TREE_MODEL_HPP
#define EE_EDITOR_SCENE_TREE_MODEL_HPP

#include <QAbstractItemModel>
#include <QPointer>

namespace ee {
class NodeGraph;
class SceneTreeItem;

class SceneTreeModel : public QAbstractItemModel {
    Q_OBJECT

private:
    using Self = SceneTreeModel;
    using Super = QAbstractItemModel;

public:
    /// Constructs a scene tree model.
    explicit SceneTreeModel(QObject* parent = nullptr);

    virtual ~SceneTreeModel() override;

    /// Sets the node graph reference.
    void setNodeGraph(NodeGraph* graph);

    virtual QVariant data(const QModelIndex& index, int role) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value,
                         int role) override;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role) const override;

    virtual QModelIndex
    index(int row, int column,
          const QModelIndex& parent = QModelIndex()) const override;

    virtual QModelIndex parent(const QModelIndex& index) const override;

    virtual int
    rowCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual int
    columnCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

protected:
    /// Constructs the scene tree item with the corresponding node graph.
    void setupTree(SceneTreeItem* item, const NodeGraph& graph);

private:
    NodeGraph* nodeGraph_;
    std::unique_ptr<SceneTreeItem> rootItem_;
};
} // namespace ee

#endif // EE_EDITOR_SCENE_TREE_MODEL_HPP
