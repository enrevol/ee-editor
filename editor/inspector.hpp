#ifndef EE_EDITOR_INSPECTOR_HPP
#define EE_EDITOR_INSPECTOR_HPP

#include <base/CCValue.h>

#include <QWidget>

namespace ee {
class NodeGraph;

class Inspector : public QWidget {
    Q_OBJECT

private:
    using Self = Inspector;
    using Super = QWidget;

public:
    explicit Inspector(QWidget* parent = nullptr);

    virtual ~Inspector() override;

    virtual void refreshPropertyValue(const NodeGraph& graph) = 0;

Q_SIGNALS:
    void propertyValueChanged(const QString& propertyName,
                              const cocos2d::Value& value);
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_VALUE_HPP
