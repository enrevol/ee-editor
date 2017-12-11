#ifndef EE_EDITOR_INSPECTOR_COLOR_HPP
#define EE_EDITOR_INSPECTOR_COLOR_HPP

#include "inspector.hpp"
#include "optional.hpp"

#include <base/ccTypes.h>

namespace Ui {
class InspectorColor;
} // namespace Ui

namespace cocos2d {
struct Color3B;
} // namespace cocos2d

namespace ee {
class InspectorColor : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorColor;
    using Super = Inspector;

public:
    using Reader = std::function<std::optional<cocos2d::Color3B>(
        const cocos2d::Node* node)>;

    using Writer =
        std::function<bool(cocos2d::Node* node, const cocos2d::Color3B& value)>;

    explicit InspectorColor(QWidget* parent = nullptr);

    virtual ~InspectorColor() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(const QColor& color);
    Self* setPropertyDisplayName(const QString& name);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(const QColor& color);

private:
    Ui::InspectorColor* ui_;
    Reader reader_;
    Writer writer_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_COLOR_HPP
