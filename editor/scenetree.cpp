#include "scenetree.hpp"

#include <parser/nodegraph.hpp>

#include <2d/CCNode.h>

namespace ee {
using Self = SceneTree;

Self::SceneTree(QWidget* parent)
    : Super(parent) {
    header()->close();
}

void Self::setNodeGraph(const NodeGraph& graph) {
    clear();

    rootItem_ = new QTreeWidgetItem(this);
    updateNode(rootItem_, graph);
}

void Self::updateNode(QTreeWidgetItem* item, const NodeGraph& graph) {
    auto name = graph.getDisplayName();
    item->setText(0, QString::fromStdString(name));
    for (auto&& child : graph.getChildren()) {
        auto childItem = new QTreeWidgetItem(item);
        updateNode(childItem, child);
    }
}
} // namespace ee
