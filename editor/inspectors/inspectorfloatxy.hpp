#ifndef EE_EDITOR_INSPECTOR_FLOAT_X_Y_HPP
#define EE_EDITOR_INSPECTOR_FLOAT_X_Y_HPP

#include "inspector.hpp"
#include "optional.hpp"

namespace Ui {
class InspectorFloatXY;
} // namespace Ui

namespace ee {
class InspectorFloatXY : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorFloatXY;
    using Super = Inspector;

public:
    using Reader = std::function<std::optional<std::pair<float, float>>(
        const cocos2d::Node* node)>;

    using Writer = std::function<bool(cocos2d::Node* node, float x, float y)>;

    explicit InspectorFloatXY(QWidget* parent = nullptr);

    virtual ~InspectorFloatXY() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(float x, float y);
    Self* setPropertyDisplayName(const QString& name);
    Self* setSubPropertyDisplayName(const QString& x, const QString& y);
    Self* setSingleStep(float value);
    Self* setValuePrecision(int precision);
    Self* setMinimumValue(float value);
    Self* setMaximumValue(float value);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(float x, float y);

protected:
    void setPropertyValueLazy(float x, float y);

private:
    Ui::InspectorFloatXY* ui_;
    Reader reader_;
    Writer writer_;
    bool updating_;
    bool refreshed_;
    QTimer* updater_;
    float valueX_;
    float valueY_;
    bool valueDirty_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_FLOAT_X_Y_HPP
