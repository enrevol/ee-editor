#ifndef EE_EDITOR_INSPECTOR_SCALE_HPP
#define EE_EDITOR_INSPECTOR_SCALE_HPP

#include "inspector.hpp"
#include "propertygetter.hpp"

#include <QDoubleSpinBox>

namespace Ui {
class InspectorScale;
} // namespace Ui

namespace ee {
class InspectorScale : public Inspector {
    Q_OBJECT

private:
    using Self = InspectorScale;
    using Super = Inspector;

public:
    explicit InspectorScale(QWidget* parent = nullptr);

    virtual ~InspectorScale() override;

    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) override;

protected:
    void setupSpinner(QDoubleSpinBox* spinner);
    void setScaleX(float value);
    void setScaleY(float value);

private:
    Ui::InspectorScale* ui_;
    FloatPropertyGetter scaleXProperty_;
    FloatPropertyGetter scaleYProperty_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_SCALE_HPP
