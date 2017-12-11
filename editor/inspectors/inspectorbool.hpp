#ifndef EE_EDITOR_INSPECTOR_BOOL_HPP
#define EE_EDITOR_INSPECTOR_BOOL_HPP

#include "inspector.hpp"
#include "optional.hpp"

namespace Ui {
class InspectorBool;
} // namespace Ui

namespace ee {
/// Inspects a bool property.
/// Used to change a node's boolean property.
class InspectorBool : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorBool;
    using Super = Inspector;

public:
    using Reader =
        std::function<std::optional<bool>(const cocos2d::Node* node)>;

    using Writer = std::function<bool(cocos2d::Node* node, bool value)>;

    explicit InspectorBool(QWidget* parent = nullptr);

    virtual ~InspectorBool() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(bool value);
    Self* setPropertyDisplayName(const QString& name);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(bool value);

private:
    Ui::InspectorBool* ui_;
    Reader reader_;
    Writer writer_;
    bool updating_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_BOOL_HPP
