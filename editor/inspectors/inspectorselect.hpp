#ifndef EE_EDITOR_INSPECTOR_SELECT_HPP
#define EE_EDITOR_INSPECTOR_SELECT_HPP

#include "inspector.hpp"
#include "optional.hpp"

namespace Ui {
class InspectorSelect;
} // namespace Ui

namespace ee {
class InspectorSelect : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorSelect;
    using Super = Inspector;

public:
    using Reader = std::function<std::optional<int>(const cocos2d::Node* node)>;
    using Writer = std::function<bool(cocos2d::Node* node, int value)>;

    explicit InspectorSelect(QWidget* parent = nullptr);

    virtual ~InspectorSelect() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(int value);
    Self* setPropertyDisplayName(const QString& name);
    Self* addSelection(const QString& name);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(int value);

private:
    Ui::InspectorSelect* ui_;
    Reader reader_;
    Writer writer_;
    bool updating_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_STRING_HPP
