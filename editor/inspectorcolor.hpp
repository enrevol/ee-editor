#ifndef EE_EDITOR_INSPECTOR_COLOR_HPP
#define EE_EDITOR_INSPECTOR_COLOR_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorColor;
} // namespace Ui

namespace ee {
class InspectorColor : public Inspector {
private:
    using Self = InspectorColor;
    using Super = Inspector;

public:
    explicit InspectorColor(QWidget* parent = nullptr);

    virtual ~InspectorColor() override;

    Self* setPropertyName(const QString& r, const QString& g, const QString& b);
    Self* setPropertyDisplayName(const QString& name);

    /// @see Super.
    virtual bool doesHandleProperty(const QString& propertyName) const override;

    /// @see Super.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) override;

protected:
    void setPropertyValue(int r, int g, int b);
    void changeColor(const QColor& color);

private:
    Ui::InspectorColor* ui_;
    std::unique_ptr<IntPropertyGetter> propertyR_;
    std::unique_ptr<IntPropertyGetter> propertyG_;
    std::unique_ptr<IntPropertyGetter> propertyB_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_COLOR_HPP
