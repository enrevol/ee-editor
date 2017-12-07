#ifndef EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
#define EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP

#include "inspectorlist.hpp"

namespace ee {
class InspectorListWidget : public InspectorList {
    Q_OBJECT

private:
    using Self = InspectorListWidget;
    using Super = InspectorList;

public:
    explicit InspectorListWidget(QWidget* parent = nullptr);

    virtual ~InspectorListWidget() override;

    /// @see Super.
    virtual void addInspector(Inspector* inspector) override;

    /// @see Super.
    virtual void clearInspectors() override;

    /// @see Super.
    virtual void
    refreshInspector(const std::vector<const cocos2d::Node*>& nodes) override;

private:
    QVector<Inspector*> inspectors_;
    QList<QMetaObject::Connection> connections_;
};
} // namespace ee

#endif // EE_EDITOR_INSPECTOR_LIST_WIDGET_HPP
