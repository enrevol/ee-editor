#ifndef EE_EDITOR_INSPECTOR_HPP
#define EE_EDITOR_INSPECTOR_HPP

#include <QWidget>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
/// Base class for all inspectors.
class Inspector : public QWidget {
    Q_OBJECT

private:
    using Self = Inspector;
    using Super = QWidget;

public:
    using Applier = std::function<bool(cocos2d::Node* node)>;

    /// Constructs an inspector.
    explicit Inspector(QWidget* parent = nullptr);

    virtual ~Inspector() override;

    /// Refreshes all properties in this inspector display for the specified
    /// node.
    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) = 0;

Q_SIGNALS:
    void propertyChanged(const Applier& applier);
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_VALUE_HPP
