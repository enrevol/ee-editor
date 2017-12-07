#ifndef EE_EDITOR_INSPECTOR_BLEND_HPP
#define EE_EDITOR_INSPECTOR_BLEND_HPP

#include "inspector.hpp"

namespace Ui {
class InspectorBlend;
} // namespace Ui

namespace cocos2d {
struct BlendFunc;
} // namespace cocos2d

namespace ee {
/// Speciailized inspector for blend func.
class InspectorBlend : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorBlend;
    using Super = Inspector;

public:
    using Reader = std::function<cocos2d::BlendFunc(const cocos2d::Node* node)>;
    using Writer = std::function<bool(cocos2d::Node* node,
                                      const cocos2d::BlendFunc& value)>;

    explicit InspectorBlend(QWidget* parent = nullptr);

    virtual ~InspectorBlend() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(int src, int dst);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(int src, int dst);

private:
    Ui::InspectorBlend* ui_;
    Reader reader_;
    Writer writer_;
    bool updating_;
    int src_;
    int dst_;
};
} // namespace ee

#endif // INSPECTORBLEND_HPP
