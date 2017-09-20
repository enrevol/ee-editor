#ifndef EE_EDITOR_NODE_INSPECTOR_HPP
#define EE_EDITOR_NODE_INSPECTOR_HPP

#include "inspectorcontainer.hpp"

namespace ee {
class NodeInspector : public InspectorContainer {
private:
    using Self = NodeInspector;
    using Super = InspectorContainer;

public:
    explicit NodeInspector(QWidget* parent = nullptr);

protected:
    virtual QVector<Inspector*> buildInspectors() override;

private:
};
} // namespace ee

#endif // EE_EDITOR_NODE_INSPECTOR_HPP
