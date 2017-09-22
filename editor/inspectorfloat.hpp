#ifndef EE_EDITOR_INSPECTOR_FLOAT_HPP
#define EE_EDITOR_INSPECTOR_FLOAT_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

#include <QWidget>

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
    Self* setValueRange(float minimum, float maximum);

    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

protected:
    void setPropertyValue(float value);

private:
    Ui::InspectorFloat* ui_;
    std::unique_ptr<FloatPropertyGetter> property_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_FLOAT_HPP
