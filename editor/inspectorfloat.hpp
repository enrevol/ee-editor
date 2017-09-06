#ifndef EE_EDITOR_INSPECTOR_FLOAT_HPP
#define EE_EDITOR_INSPECTOR_FLOAT_HPP

#include <QWidget>

namespace Ui {
class InspectorFloat;
} // namespace Ui

namespace ee {
class InspectorFloat : public QWidget {
    Q_OBJECT

private:
    using Self = InspectorFloat;
    using Super = QWidget;

public:
    explicit InspectorFloat(QWidget* parent = nullptr);
    virtual ~InspectorFloat() override;

private:
    Ui::InspectorFloat* ui;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_FLOAT_HPP
