#include "inspectorcontainer.hpp"
#include "inspector.hpp"

#include <QVBoxLayout>

namespace ee {
using Self = InspectorContainer;

Self::InspectorContainer(QWidget* parent)
    : Super(parent)
    , initialized_(false) {}

void Self::initialize() {
    Q_ASSERT(not initialized_);

    auto verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(3);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(verticalLayout);

    inspectors_ = buildInspectors();
    for (auto&& inspector : inspectors_) {
        verticalLayout->addWidget(inspector);
        connect(
            inspector, &Inspector::propertyValueChanged,
            [this](const QString& propertyName, const cocos2d::Value& value) {
                Q_EMIT propertyValueChanged(propertyName, value);
            });
    }

    initialized_ = true;
}

const QVector<Inspector*>& Self::getInspectors() const {
    Q_ASSERT(initialized_);
    return inspectors_;
}

void Self::refreshPropertyValue(const NodeGraph& graph) {
    for (auto&& inspector : getInspectors()) {
        inspector->refreshPropertyValue(graph);
    }
}
} // namespace ee
