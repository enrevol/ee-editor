#ifndef EE_EDITOR_INSPECTOR_BOOL_HPP
#define EE_EDITOR_INSPECTOR_BOOL_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorBool;
} // namespace Ui

namespace ee {
class InspectorBool : public Inspector {
private:
    using Self = InspectorBool;
    using Super = Inspector;

public:
    explicit InspectorBool(QWidget* parent = nullptr);

    virtual ~InspectorBool() override;

    Self* setPropertyName(const QString& name);
    Self* setPropertyDisplayName(const QString& name);

    /// @see Super.
    virtual bool doesHandleProperty(const QString& propertyName) const override;

    /// @see Super.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) override;

protected:
    void setPropertyValue(bool value);

private:
    Ui::InspectorBool* ui_;
    bool updating_;
    std::unique_ptr<BoolPropertyGetter> property_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_BOOL_HPP
