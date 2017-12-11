#ifndef EE_EDITOR_INSPECTOR_STRING_HPP
#define EE_EDITOR_INSPECTOR_STRING_HPP

#include "inspector.hpp"
#include "optional.hpp"

namespace Ui {
class InspectorString;
} // namespace Ui

namespace ee {
class InspectorString : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorString;
    using Super = Inspector;

public:
    using Reader =
        std::function<std::optional<std::string>(const cocos2d::Node* node)>;

    using Writer =
        std::function<bool(cocos2d::Node* node, const std::string& value)>;

    explicit InspectorString(QWidget* parent = nullptr);

    virtual ~InspectorString() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(const QString& value);
    Self* setPropertyDisplayName(const QString& name);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(const QString& value);

private:
    Ui::InspectorString* ui_;
    Reader reader_;
    Writer writer_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_STRING_HPP
