#ifndef EE_EDITOR_GLSL_EDIT_SIDEBAR_HPP
#define EE_EDITOR_GLSL_EDIT_SIDEBAR_HPP

#include <QWidget>

namespace ee {
class GLSLEdit;

struct GLSLEditBlockInfo {
    int position;
    int number;
};

class GLSLEditSidebar : public QWidget {
private:
    using Self = GLSLEditSidebar;
    using Super = QWidget;

public:
    explicit GLSLEditSidebar(GLSLEdit* editor);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    friend class GLSLEdit;

    QVector<GLSLEditBlockInfo> lineNumbers_;
    QColor backgroundColor_;
    QColor lineNumberColor_;
    QFont font_;
    int rightMargin_;
};
} // namespace ee

#endif // EE_EDITOR_GLSL_EDIT_SIDEBAR_HPP
