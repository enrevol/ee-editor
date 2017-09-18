#include "scenetree.hpp"
#include "config.hpp"
#include "scenetreemodel.hpp"

#include <parser/nodegraph.hpp>

#include <2d/CCNode.h>

namespace ee {
using Self = SceneTree;

Self::SceneTree(QWidget* parent)
    : Super(parent) {
    connect(&Config::getInstance(), &Config::interfaceLoaded,
            [this](const QFileInfo& path) {
                setNodeGraph(Config::getInstance()
                                 .getInterfaceSettings()
                                 ->getNodeGraph()
                                 .value());
            });
}

void Self::setNodeGraph(const NodeGraph& graph) {
    treeModel_ = new SceneTreeModel(this);
    treeModel_->setNodeGraph(graph);
    setModel(treeModel_);
}
} // namespace ee
