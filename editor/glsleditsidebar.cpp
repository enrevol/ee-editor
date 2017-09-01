#include "glsleditsidebar.hpp"
#include "glsledit.hpp"

#include <QPainter>

namespace ee {
using Self = GLSLEditSidebar;

Self::GLSLEditSidebar(GLSLEdit* editor)
    : Super(editor) {
    backgroundColor_ = Qt::GlobalColor::lightGray;
    lineNumberColor_ = Qt::GlobalColor::black;
}

void Self::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), backgroundColor_);
    painter.setPen(lineNumberColor_);
    painter.setFont(font_);

    int fontHeight = QFontMetrics(font_).height();
    for (auto&& line : lineNumbers_) {
        painter.drawText(0, line.position, width() - rightMargin_, fontHeight,
                         Qt::AlignmentFlag::AlignRight,
                         QString::number(line.number));
    }
}
} // namespace ee
