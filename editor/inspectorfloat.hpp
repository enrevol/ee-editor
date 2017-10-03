#ifndef EE_EDITOR_INSPECTOR_FLOAT_HPP
#define EE_EDITOR_INSPECTOR_FLOAT_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorFloat;
} // namespace Ui

namespace ee {
class InspectorFloat : public Inspector {
private:
    using Self = InspectorFloat;
    using Super = Inspector;

public:
    explicit InspectorFloat(QWidget* parent = nullptr);

    virtual ~InspectorFloat() override;

    Self* setPropertyName(const QString& name);
    Self* setPropertyDisplayName(const QString& name);
    Self* setSingleStep(float value);
    Self* setValuePrecision(int precision);
    Self* setMinimumValue(float value);
    Self* setMaximumValue(float value);

    /// @see Super.
    virtual bool doesHandleProperty(const QString& propertyName) const override;

    /// @see Super.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) override;

protected:
    void setPropertyValue(float value);

private:
    Ui::InspectorFloat* ui_;
    bool updating_;
    std::unique_ptr<FloatPropertyGetter> property_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_FLOAT_HPP
