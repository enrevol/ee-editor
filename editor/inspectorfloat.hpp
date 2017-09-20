#ifndef EE_EDITOR_INSPECTOR_FLOAT_HPP
#define EE_EDITOR_INSPECTOR_FLOAT_HPP

#include "inspector.hpp"

#include <QWidget>

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
    explicit InspectorFloat(const QString& propertyName,
                            QWidget* parent = nullptr);

    virtual ~InspectorFloat() override;

    Self* setPropertyDisplayName(const QString& name);
    Self* setValuePrecision(int precision);
    Self* setMinimumValue(float value);
    Self* setMaximumValue(float value);
    Self* setValueRange(float minimum, float maximum);

    virtual void refreshPropertyValue(const NodeGraph& graph) override;

Q_SIGNALS:
    void valueChanged(float value);

private:
    QString propertyName_;
    Ui::InspectorFloat* ui_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_FLOAT_HPP
