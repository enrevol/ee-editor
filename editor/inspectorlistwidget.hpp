#ifndef EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
#define EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP

#include <QWidget>

namespace ee {
class InspectorContainer;

class InspectorListWidget : public QWidget {
private:
    using Self = InspectorListWidget;
    using Super = QWidget;

public:
    explicit InspectorListWidget(QWidget* parent = nullptr);

    void addInspector(InspectorContainer* inspector);

    void clearInspectors();

protected:
private:
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
