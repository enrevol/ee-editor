#ifndef EE_EDITOR_NODE_INSPECTOR_HPP
#define EE_EDITOR_NODE_INSPECTOR_HPP

#include "inspectorgroup.hpp"

namespace ee {
class NodeInspector : public InspectorGroup {
private:
    using Self = NodeInspector;
    using Super = InspectorGroup;

public:
    explicit NodeInspector(QWidget* parent = nullptr);

private:
};
} // namespace ee

#endif // EE_EDITOR_NODE_INSPECTOR_HPP
