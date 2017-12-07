#ifndef EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
#define EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP

#include "inspectorlist.hpp"

namespace ee {
class NodeGraph;
class SelectionPath;
class SelectionTree;

class InspectorListWidget : public InspectorList {
    Q_OBJECT

private:
    using Self = InspectorListWidget;
    using Super = InspectorList;

public:
    explicit InspectorListWidget(QWidget* parent = nullptr);

    virtual ~InspectorListWidget() override;

    void addInspector(Inspector* inspector);

    void clearInspectors();

    void setSelection(const NodeGraph& graph, const SelectionTree& selection);

    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

Q_SIGNALS:
   // void propertyValueChanged(const SelectionPath& path,
   //                           const QString& propertyName,
   //                           const cocos2d::Value& value);

private:
    const NodeGraph* nodeGraph_;
    std::unique_ptr<SelectionTree> selection_;
    QVector<Inspector*> inspectors_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
