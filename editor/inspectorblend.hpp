#ifndef EE_EDITOR_INSPECTOR_BLEND_HPP
#define EE_EDITOR_INSPECTOR_BLEND_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorBlend;
} // namespace Ui

namespace ee {
class InspectorBlend : public Inspector {
private:
    using Self = InspectorBlend;
    using Super = Inspector;

public:
    explicit InspectorBlend(QWidget* parent = nullptr);

    virtual ~InspectorBlend() override;

    Self* setPropertyName(const QString& src, const QString& dst);

    /// @see Super.
    virtual bool doesHandleProperty(const QString& propertyName) const override;

    /// @see Super.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) override;

protected:
    void setPropertyValue(int src, int dst);

private:
    Ui::InspectorBlend* ui_;
    bool updating_;
    std::unique_ptr<IntPropertyGetter> propertySrc_;
    std::unique_ptr<IntPropertyGetter> propertyDst_;
};
} // namespace ee

#endif // INSPECTORBLEND_HPP
