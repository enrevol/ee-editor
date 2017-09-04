#include <ciso646>

#include "glsledit.hpp"
#include "glslcomponent.hpp"
#include "glsleditsidebar.hpp"
#include "glslhighlighter.hpp"

#include <QMenu>

namespace ee {
using Self = GLSLEdit;

Self::GLSLEdit(QWidget* parent)
    : Super(parent) {
    highlighter_ = new GLSLHighlighter(document());
    sidebar_ = new GLSLEditSidebar(this);
    showLineNumbers_ = true;
    textWrap_ = true;

    connect(this, &Self::cursorPositionChanged, this, &Self::updateCursor);
    connect(this, &Self::blockCountChanged, [this] { updateSidebar(); });
    connect(this, &Self::updateRequest,
            [this](const QRect& rect, int dy) { updateSidebar(rect, dy); });

    setFont(QFont("Consolas"));
}

Self::~GLSLEdit() {}

void Self::setColor(GLSLComponent component, const QColor& color) {
    if (component == GLSLComponent::Background) {
        auto pal = palette();
        pal.setColor(QPalette::ColorRole::Base, color);
        setPalette(pal);
        return;
    }
    if (component == GLSLComponent::Normal) {
        auto pal = palette();
        pal.setColor(QPalette::ColorRole::Text, color);
        setPalette(pal);
        return;
    }
    if (component == GLSLComponent::Sidebar) {
        sidebar_->backgroundColor_ = color;
        updateSidebar();
        return;
    }
    if (component == GLSLComponent::LineNumber) {
        sidebar_->lineNumberColor_ = color;
        updateSidebar();
        return;
    }
    if (component == GLSLComponent::Cursor) {
        cursorColor_ = color;
        updateCursor();
        return;
    }
    highlighter_->setColor(component, color);
    updateCursor();
}

bool Self::isLineNumbersVisible() const {
    return showLineNumbers_;
}

void Self::setLineNumbersVisible(bool visible) {
    showLineNumbers_ = visible;
    updateSidebar();
}

bool Self::isTextWrapEnabled() const {
    return textWrap_;
}

void Self::setTextWrapEnabled(bool enabled) {
    textWrap_ = enabled;
    setLineWrapMode(enabled ? QPlainTextEdit::LineWrapMode::WidgetWidth
                            : QPlainTextEdit::LineWrapMode::NoWrap);
}

void Self::resizeEvent(QResizeEvent* event) {
    Super::resizeEvent(event);
    updateSidebar();
}

void Self::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() == Qt::KeyboardModifier::ControlModifier) {
        int steps = event->delta() / 20;
        steps = qBound(-3, steps, 3);

        QFont textFont = font();
        int pointSize = textFont.pointSize() + steps;
        pointSize = qBound(10, pointSize, 40);

        textFont.setPointSize(pointSize);
        setFont(textFont);

        updateSidebar();
        event->accept();
        return;
    }
    Super::wheelEvent(event);
}

void Self::contextMenuEvent(QContextMenuEvent* event) {
    auto menu = createStandardContextMenu();
    menu->addAction("Indent Code", this, &Self::indent);
    menu->exec(event->globalPos());
    delete menu;
}

void Self::mark(const QString& text, Qt::CaseSensitivity sensitivity) {
    highlighter_->mark(text, sensitivity);
}

void Self::indent() {
    //
}

void Self::updateCursor() {
    if (isReadOnly()) {
        setExtraSelections(QList<QTextEdit::ExtraSelection>());
        return;
    }
}

void Self::updateSidebar(const QRect& rect, int dy) {
    Q_UNUSED(rect);
    if (dy != 0) {
        updateSidebar();
    }
}

void Self::updateSidebar() {
    if (not showLineNumbers_) {
        // Hide the sidebar.
        sidebar_->hide();
        setViewportMargins(0, 0, 0, 0);
        sidebar_->setGeometry(0, 0, 0, height());
        return;
    }

    // Show the sidebar.
    sidebar_->font_ = font();
    sidebar_->show();

    // Calculate the sidebar's width.
    int digits = 1;
    int maxLines = blockCount();
    for (int number = 10; number <= maxLines; number *= 10) {
        ++digits;
    }

    auto fontWidth = fontMetrics().width('w');
    constexpr int margin = 5;
    auto sidebarWidth = fontWidth * digits + margin * 2;
    setViewportMargins(sidebarWidth, 0, 0, 0);
    sidebar_->rightMargin_ = margin;
    sidebar_->setGeometry(0, 0, sidebarWidth, height());

    // Update the line numbers' info in sidebar.
    QRectF sidebarRect(0, 0, sidebarWidth, height());
    auto block = firstVisibleBlock();
    int index = 0;
    while (block.isValid()) {
        if (block.isVisible()) {
            QRectF rect =
                blockBoundingGeometry(block).translated(contentOffset());
            if (sidebarRect.intersects(rect)) {
                auto&& lineNumbers = sidebar_->lineNumbers_;
                if (lineNumbers.count() <= index) {
                    lineNumbers.resize(index + 1);
                }
                auto&& lineMumber = lineNumbers[index];
                lineMumber.position = rect.top();
                lineMumber.number = block.blockNumber() + 1;
                ++index;
            }
        }
        block = block.next();
    }
    sidebar_->lineNumbers_.resize(index);
    sidebar_->update();
}
} // namespace ee
