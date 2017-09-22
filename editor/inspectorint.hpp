#ifndef EE_EDITOR_INSPECTOR_INT_HPP
#define EE_EDITOR_INSPECTOR_INT_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorInt;
} // namespace Ui

namespace ee {
class InspectorInt : public Inspector {
private:
    using Self = InspectorInt;
    using Super = Inspector;

public:
    explicit InspectorInt(QWidget* parent = nullptr);

    virtual ~InspectorInt() override;

    Self* setPropertyName(const QString& name);
    Self* setPropertyDisplayName(const QString& name);
    Self* setSingleStep(int value);
    Self* setMinimumValue(int value);
    Self* setMaximumValue(int value);

    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

protected:
    void setPropertyValue(int value);

private:
    Ui::InspectorInt* ui_;
    std::unique_ptr<IntPropertyGetter> property_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_INT_HPP
