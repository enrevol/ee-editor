#ifndef EE_EDITOR_INSPECTOR_CONTAINER_HPP
#define EE_EDITOR_INSPECTOR_CONTAINER_HPP

#include <base/CCValue.h>

#include <QWidget>

namespace ee {
class Inspector;
class NodeGraph;

class InspectorContainer : public QWidget {
    Q_OBJECT

private:
    using Self = InspectorContainer;
    using Super = QWidget;

public:
    explicit InspectorContainer(QWidget* parent = nullptr);

    void initialize();

    const QVector<Inspector*>& getInspectors() const;

    void refreshPropertyValue(const NodeGraph& graph);

Q_SIGNALS:
    void propertyValueChanged(const QString& propertyName,
                              const cocos2d::Value& value);

protected:
    virtual QVector<Inspector*> buildInspectors() = 0;

private:
    bool initialized_;
    QVector<Inspector*> inspectors_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_CONTAINER_HPP
