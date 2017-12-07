#ifndef EE_EDITOR_INSPECTOR_TEXTURE_HPP
#define EE_EDITOR_INSPECTOR_TEXTURE_HPP

#include "inspector.hpp"

namespace Ui {
class InspectorTexture;
} // namespace Ui

namespace ee {
class InspectorTexture : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorTexture;
    using Super = Inspector;

public:
    using Reader = std::function<std::string(const cocos2d::Node* node)>;
    using Writer =
        std::function<bool(cocos2d::Node* node, const std::string& value)>;

    explicit InspectorTexture(QWidget* parent = nullptr);

    virtual ~InspectorTexture() override;

    Self* setReader(const Reader& reader);
    Self* setWriter(const Writer& writer);
    Self* setPropertyValue(const QString& value);
    Self* setPropertyDisplayName(const QString& name);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
    void propertyValueChanged(const QString& value);
    void contentSizeResetRequested();

protected:
    Self* setPropertyValue(const QString& value, bool notify);

    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dragMoveEvent(QDragMoveEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;

private:
    Ui::InspectorTexture* ui_;
    Reader reader_;
    Writer writer_;
    bool updating_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_TEXTURE_HPP
