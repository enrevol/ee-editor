#ifndef EE_EDITOR_INSPECTOR_CONTAINER_HPP
#define EE_EDITOR_INSPECTOR_CONTAINER_HPP

#include "inspector.hpp"

#include <base/CCValue.h>

#include <QWidget>

namespace ee {
class Inspector;
class NodeGraph;

/// Groups many inspectors.
class InspectorContainer : public Inspector {
private:
    using Self = InspectorContainer;
    using Super = Inspector;

public:
    explicit InspectorContainer(QWidget* parent = nullptr);

    void initialize();

    const QVector<Inspector*>& getInspectors() const;

    /// @see Super.
    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

protected:
    virtual QVector<Inspector*> buildInspectors() = 0;

private:
    bool initialized_;
    QVector<Inspector*> inspectors_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_CONTAINER_HPP
