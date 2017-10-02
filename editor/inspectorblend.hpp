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

    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

    virtual bool refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection,
                                      const QString& propertyName) override;

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
