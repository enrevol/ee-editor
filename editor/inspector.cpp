#include "inspector.hpp"

namespace ee {
using Self = Inspector;

Self::Inspector(QWidget* parent)
    : Super(parent) {}

Self::~Inspector() {}

bool Self::refreshProperty(const NodeGraph& graph,
                           const SelectionTree& selection,
                           const QString& propertyName) {
    if (not doesHandleProperty(propertyName)) {
        return false;
    }
    refreshInspector(graph, selection);
    return true;
}
} // namespace ee
