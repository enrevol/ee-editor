#ifndef EE_EDITOR_GLSL_HIGHLIGHTER_HPP
#define EE_EDITOR_GLSL_HIGHLIGHTER_HPP

#include <QRegularExpression>
#include <QSyntaxHighlighter>

namespace ee {
enum class GLSLComponent;

class GLSLHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

private:
    using Self = GLSLHighlighter;
    using Super = QSyntaxHighlighter;

public:
    explicit GLSLHighlighter(QTextDocument* parent = nullptr);

    void setColor(GLSLComponent component, const QColor& color);
    void mark(const QString& text, Qt::CaseSensitivity sensitivity);

protected:
    virtual void highlightBlock(const QString& text) override;

private:
    QSet<QString> keywords_;
    QSet<QString> types_;
    QSet<QString> builtIns_;
    QMap<GLSLComponent, QColor> colors_;
    QString markString_;
    Qt::CaseSensitivity markSensitivity_;
};
} // namespace ee

#endif // EE_EDITOR_GLSL_HIGHLIGHTER_HPP
