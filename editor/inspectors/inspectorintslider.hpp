#ifndef EE_EDITOR_INSPECTOR_INT_SLIDER_HPP
#define EE_EDITOR_INSPECTOR_INT_SLIDER_HPP

#include "inspector.hpp"

namespace Ui {
class InspectorIntSlider;
} // namespace Ui

namespace ee {
class InspectorIntSlider : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorIntSlider;
    using Super = Inspector;

public:
    using Reader = std::function<int(const cocos2d::Node* node)>;
    using Writer = std::function<bool(cocos2d::Node* node, int value)>;

    explicit InspectorIntSlider(QWidget* parent = nullptr);

    virtual ~InspectorIntSlider() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(int value);
    Self* setPropertyDisplayName(const QString& name);
    Self* setSingleStep(int value);
    Self* setMinimumValue(int value);
    Self* setMaximumValue(int value);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(int value);

private:
    Ui::InspectorIntSlider* ui_;
    Reader reader_;
    Writer writer_;
    bool updating_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_INT_SLIDER_HPP
