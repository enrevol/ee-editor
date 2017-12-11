#ifndef EE_EDITOR_INSPECTOR_FLOAT_HPP
#define EE_EDITOR_INSPECTOR_FLOAT_HPP

#include "inspector.hpp"
#include "optional.hpp"

namespace Ui {
class InspectorFloat;
} // namespace Ui

namespace ee {
class InspectorFloat : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorFloat;
    using Super = Inspector;

public:
    using Reader =
        std::function<std::optional<float>(const cocos2d::Node* node)>;
    using Writer = std::function<bool(cocos2d::Node* node, float value)>;

    explicit InspectorFloat(QWidget* parent = nullptr);

    virtual ~InspectorFloat() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(float value);
    Self* setPropertyDisplayName(const QString& name);
    Self* setSingleStep(float value);
    Self* setValuePrecision(int precision);
    Self* setMinimumValue(float value);
    Self* setMaximumValue(float value);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(float value);

private:
    Ui::InspectorFloat* ui_;
    Reader reader_;
    Writer writer_;
    bool updating_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_FLOAT_HPP
