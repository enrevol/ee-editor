#ifndef EE_EDITOR_INSPECTOR_TEXTURE_HPP
#define EE_EDITOR_INSPECTOR_TEXTURE_HPP

#include <QWidget>

namespace Ui {
class InspectorTexture;
} // namespace Ui

namespace ee {
class InspectorTexture : public QWidget {
    Q_OBJECT

private:
    using Self = InspectorTexture;
    using Super = QWidget;

public:
    explicit InspectorTexture(QWidget* parent = 0);

    virtual ~InspectorTexture() override;

private:
    Ui::InspectorTexture* ui;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_TEXTURE_HPP
