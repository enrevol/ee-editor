#ifndef EE_EDITOR_GLSL_EDIT_HPP
#define EE_EDITOR_GLSL_EDIT_HPP

#include <QPlainTextEdit>

namespace ee {
enum class GLSLComponent;

class GLSLEditSidebar;
class GLSLHighlighter;

/// https://github.com/apitrace/apitrace/blob/master/gui/glsledit.h
class GLSLEdit : public QPlainTextEdit {
    Q_OBJECT

private:
    using Self = GLSLEdit;
    using Super = QPlainTextEdit;

public:
    explicit GLSLEdit(QWidget* parent = nullptr);
    virtual ~GLSLEdit() override;

    void setColor(GLSLComponent component, const QColor& color);

    bool isLineNumbersVisible() const;
    bool isTextWrapEnabled() const;

public Q_SLOTS:
    void updateSidebar();
    void mark(const QString& text, Qt::CaseSensitivity sensitivity);
    void setLineNumbersVisible(bool visible);
    void setTextWrapEnabled(bool enabled);
    void indent();

protected:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void contextMenuEvent(QContextMenuEvent* event) override;

private Q_SLOTS:
    void updateCursor();
    void updateSidebar(const QRect& rect, int dy);

private:
    GLSLHighlighter* highlighter_;
    GLSLEditSidebar* sidebar_;
    QColor cursorColor_;
    bool showLineNumbers_;
    bool textWrap_;
};
} // namespace ee

#endif // EE_EDITOR_GLSL_EDIT_HPP
