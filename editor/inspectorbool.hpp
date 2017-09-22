#ifndef EE_EDITOR_INSPECTOR_BOOL_HPP
#define EE_EDITOR_INSPECTOR_BOOL_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorBool;
} // namespace Ui

namespace ee {
class InspectorBool : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorBool;
    using Super = Inspector;

public:
    explicit InspectorBool(const QString& propertyName,
                           QWidget* parent = nullptr);

    virtual ~InspectorBool() override;

    Self* setPropertyDisplayName(const QString& name);

    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

protected:
    void setPropertyValue(bool value);

private:
    BoolPropertyGetter property_;
    Ui::InspectorBool* ui_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_BOOL_HPP
