#ifndef EE_EDITOR_INSPECTOR_GROUP_HPP
#define EE_EDITOR_INSPECTOR_GROUP_HPP

#include "inspector.hpp"

namespace Ui {
class InspectorGroup;
} // namespace Ui

namespace ee {
class InspectorGroup : public Inspector {
private:
    using Self = InspectorGroup;
    using Super = Inspector;

public:
    explicit InspectorGroup(QWidget* parent = nullptr);

    virtual ~InspectorGroup() override;

    void setDisplayName(const QString& name);

    /// @see Super.
    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

protected:
    void addInspector(Inspector* inspector);

private:
    Ui::InspectorGroup* ui_;
    QVector<Inspector*> inspectors_;
};
} // namespace ee

#endif // INSPECTORGROUP_HPP
