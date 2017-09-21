#ifndef EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
#define EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP

#include <base/CCValue.h>

#include <QWidget>

namespace ee {
class Inspector;
class NodeGraph;
class SceneSelection;

class InspectorListWidget : public QWidget {
    Q_OBJECT

private:
    using Self = InspectorListWidget;
    using Super = QWidget;

public:
    explicit InspectorListWidget(QWidget* parent = nullptr);

    virtual ~InspectorListWidget() override;

    void addInspector(Inspector* inspector);

    void clearInspectors();

    void refreshPropertyValue(const NodeGraph& graph,
                              const SceneSelection& selection);

Q_SIGNALS:
    void propertyValueChanged(const NodeGraph& graph,
                              const SceneSelection& selection,
                              const QString& propertyName,
                              const cocos2d::Value& value);

private:
    const NodeGraph* nodeGraph_;
    std::unique_ptr<SceneSelection> selection_;
    QVector<Inspector*> inspectors_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
