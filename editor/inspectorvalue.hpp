#ifndef EE_EDITOR_INSPECTOR_VALUE_HPP
#define EE_EDITOR_INSPECTOR_VALUE_HPP

#include <base/CCValue.h>

#include <QWidget>

namespace ee {
class NodeGraph;

class InspectorValue : public QWidget {
    Q_OBJECT

private:
    using Self = InspectorValue;
    using Super = QWidget;

public:
    explicit InspectorValue(QWidget* parent = nullptr);

    virtual ~InspectorValue() override;

    virtual void refreshPropertyValue(const NodeGraph& graph) = 0;

Q_SIGNALS:
    void propertyValueChanged(const QString& propertyName,
                              const cocos2d::Value& value);
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_VALUE_HPP
