#include "scenetree.hpp"
#include "scenetreemodel.hpp"

#include <parser/nodegraph.hpp>

#include <2d/CCNode.h>

namespace ee {
using Self = SceneTree;

Self::SceneTree(QWidget* parent)
    : Super(parent) {}

void Self::setNodeGraph(const NodeGraph& graph) {
    treeModel_ = new SceneTreeModel();
    treeModel_->setNodeGraph(graph);
    setModel(treeModel_);
}
} // namespace ee
