#ifndef EE_EDITOR_INSPECTOR_INT_SLIDER_HPP
#define EE_EDITOR_INSPECTOR_INT_SLIDER_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorIntSlider;
} // namespace Ui

namespace ee {
class InspectorIntSlider : public Inspector {
private:
    using Self = InspectorIntSlider;
    using Super = Inspector;

public:
    explicit InspectorIntSlider(QWidget* parent = nullptr);

    virtual ~InspectorIntSlider() override;

    Self* setPropertyName(const QString& name);
    Self* setPropertyDisplayName(const QString& name);
    Self* setSingleStep(int value);
    Self* setMinimumValue(int value);
    Self* setMaximumValue(int value);

    /// @see Super.
    virtual bool doesHandleProperty(const QString& propertyName) const override;

    /// @see Super.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) override;

protected:
    void setPropertyValue(int value);

private:
    Ui::InspectorIntSlider* ui_;
    bool updating_;
    std::unique_ptr<IntPropertyGetter> property_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_INT_SLIDER_HPP
