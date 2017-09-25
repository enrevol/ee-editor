#include "clickablewidget.hpp"

namespace ee {
using Self = ClickableWidget;

Self::ClickableWidget(QWidget* parent)
    : Super(parent) {}

Self::~ClickableWidget() {}

void Self::mousePressEvent(QMouseEvent* event) {
    Super::mousePressEvent(event);
    Q_EMIT clicked();
}
} // namespace ee
