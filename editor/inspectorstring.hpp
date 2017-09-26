#ifndef EE_EDITOR_INSPECTOR_STRING_HPP
#define EE_EDITOR_INSPECTOR_STRING_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorString;
} // namespace Ui

namespace ee {
class InspectorString : public Inspector {
private:
    using Self = InspectorString;
    using Super = Inspector;

public:
    explicit InspectorString(QWidget* parent = nullptr);

    virtual ~InspectorString() override;

    Self* setPropertyName(const QString& name);
    Self* setPropertyDisplayName(const QString& name);

    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

protected:
    void setPropertyValue(const QString& value);

private:
    Ui::InspectorString* ui_;
    std::unique_ptr<StringPropertyGetter> property_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_STRING_HPP
