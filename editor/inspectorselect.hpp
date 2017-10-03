#ifndef EE_EDITOR_INSPECTOR_SELECT_HPP
#define EE_EDITOR_INSPECTOR_SELECT_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorSelect;
} // namespace Ui

namespace ee {
class InspectorSelect : public Inspector {
private:
    using Self = InspectorSelect;
    using Super = Inspector;

public:
    explicit InspectorSelect(QWidget* parent = nullptr);

    virtual ~InspectorSelect() override;

    Self* setPropertyName(const QString& name);
    Self* setPropertyDisplayName(const QString& name);
    Self* addSelection(const QString& name);

    /// @see Super.
    virtual bool doesHandleProperty(const QString& propertyName) const override;

    /// @see Super.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) override;

protected:
    void setPropertyValue(int value);

private:
    Ui::InspectorSelect* ui_;
    bool updating_;
    std::unique_ptr<IntPropertyGetter> property_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_STRING_HPP
