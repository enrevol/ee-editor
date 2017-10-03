#ifndef EE_EDITOR_INSPECTOR_TEXTURE_HPP
#define EE_EDITOR_INSPECTOR_TEXTURE_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

namespace Ui {
class InspectorTexture;
} // namespace Ui

namespace ee {
class InspectorTexture : public Inspector {
private:
    using Self = InspectorTexture;
    using Super = Inspector;

public:
    explicit InspectorTexture(QWidget* parent = nullptr);

    virtual ~InspectorTexture() override;

    Self* setPropertyName(const QString& tex, const QString& w,
                          const QString& h);
    Self* setPropertyDisplayName(const QString& name);

    /// @see Super.
    virtual bool doesHandleProperty(const QString& propertyName) const override;

    /// @see Super.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) override;

protected:
    void setPropertyValue(const QString& value, bool notify);

    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dragMoveEvent(QDragMoveEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;

private:
    Ui::InspectorTexture* ui_;
    bool updating_;
    std::unique_ptr<StringPropertyGetter> propertyTex_;
    std::unique_ptr<FloatPropertyGetter> propertyW_;
    std::unique_ptr<FloatPropertyGetter> propertyH_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_TEXTURE_HPP
