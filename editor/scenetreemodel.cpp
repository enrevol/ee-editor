#include "scenetreemodel.hpp"

#include <parser/nodegraph.hpp>

namespace ee {
using Self = SceneTreeModel;

Self::SceneTreeModel(QObject* parent)
    : Super(parent) {}

Self::~SceneTreeModel() {}

void Self::setNodeGraph(const NodeGraph& graph) {
    nodeGraph_ = std::make_unique<NodeGraph>(graph);
}

QVariant Self::data(const QModelIndex& index, int role) const {
    return QVariant();
}

bool Self::setData(const QModelIndex& index, const QVariant& value, int role) {
    return false;
}

QVariant Self::headerData(int section, Qt::Orientation orientation,
                          int role) const {
    return QVariant();
}

QModelIndex Self::index(int row, int column, const QModelIndex& parent) const {
    return QModelIndex();
}

QModelIndex Self::parent(const QModelIndex& index) const {
    return QModelIndex();
}

int Self::rowCount(const QModelIndex& parent) const {
    return 0;
}

int Self::columnCount(const QModelIndex& parent) const {
    return 0;
}

Qt::ItemFlags Self::flags(const QModelIndex& index) const {
    return Qt::ItemFlag::NoItemFlags;
}
} // namespace ee
