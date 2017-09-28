#ifndef EE_EDITOR_INSPECTOR_HPP
#define EE_EDITOR_INSPECTOR_HPP

#include <base/CCValue.h>

#include <QWidget>

namespace ee {
class NodeGraph;
class SelectionTree;

/// Base class for all inspectors.
class Inspector : public QWidget {
    Q_OBJECT

private:
    using Self = Inspector;
    using Super = QWidget;

public:
    /// Constructs an inspector.
    explicit Inspector(QWidget* parent = nullptr);

    virtual ~Inspector() override;

    /// Refresh this inspector display with the specified graph and selection.
    /// @param graph The current scene graph.
    /// @param selection The current scene selection.
    virtual void refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection) = 0;

    virtual bool refreshPropertyValue(const NodeGraph& graph,
                                      const SelectionTree& selection,
                                      const QString& propertyName) = 0;

Q_SIGNALS:
    /// Occurs when this inspector properties values have changed.
    /// @param propertyName The property name.
    /// @param value New value of the property.
    void propertyValueChanged(const QString& propertyName,
                              const cocos2d::Value& value);
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_VALUE_HPP
