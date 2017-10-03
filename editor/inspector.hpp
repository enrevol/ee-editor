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

    /// Checks whether this inspector handles the specified property.
    /// @param propertyName The property's name.
    /// @param True if this inspector can handles the specified property, false
    /// otherwise.
    virtual bool doesHandleProperty(const QString& propertyName) const = 0;

    /// Refreshes all properties in this inspector display with the specified
    /// graph and selection.
    /// @param graph The current scene graph.
    /// @param selection The current scene selection.
    virtual void refreshInspector(const NodeGraph& graph,
                                  const SelectionTree& selection) = 0;

    /// Refreshes this inspector display with the specified graph, selection and
    /// property.
    /// @param graph The current scene graph.
    /// @param selection The current scene selection.
    /// @param propertyName The property's name.
    /// @return True if the property is handled, false otherwise.
    virtual bool refreshProperty(const NodeGraph& graph,
                                 const SelectionTree& selection,
                                 const QString& propertyName);

Q_SIGNALS:
    /// Occurs when this inspector properties values have changed.
    /// @param propertyName The property name.
    /// @param value New value of the property.
    void propertyValueChanged(const QString& propertyName,
                              const cocos2d::Value& value);

    /// Occurs when the inspector properties values have changed and the
    /// specified property needs to be reassigned.
    /// @param propertyName The property name.
    void propertyNeedReassign(const QString& propertyName);

    /// Occurs when the inspector properties values have changed and affects the
    /// specified property.
    /// @param propertyName The property name.
    void propertyNeedRefresh(const QString& propertyName);
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_VALUE_HPP
