#ifndef EE_EDITOR_OPEN_GL_WIDGET_HPP
#define EE_EDITOR_OPEN_GL_WIDGET_HPP

#include <platform/qt/CCOpenGLWidget_Qt.hpp>

namespace ee {
class OpenGLWidget : public cocos2d::OpenGLWidget {
    Q_OBJECT
private:
    using Self = OpenGLWidget;
    using Super = cocos2d::OpenGLWidget;

public:
    OpenGLWidget(QWidget* parent = nullptr);
    virtual ~OpenGLWidget() override;
};
} // namespace ee

#endif // EE_EDITOR_OPEN_GL_WIDGET_HPP
