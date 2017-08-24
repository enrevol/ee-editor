#ifndef EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP
#define EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP

#include "platform/CCPlatformMacros.h"

#include <QOpenGLWidget>

NS_CC_BEGIN
using MouseEventCallback = std::function<void(QMouseEvent* event)>;
using ResizeEventCallback = std::function<void(QResizeEvent* event)>;
using KeyEventCallback = std::function<void(QKeyEvent* event)>;

class CC_DLL OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT

private:
    using Self = OpenGLWidget;
    using Super = QOpenGLWidget;

public:
    explicit OpenGLWidget(QWidget* parent = nullptr, int width = 800,
                          int height = 600);

    virtual ~OpenGLWidget() override;

    void setMouseMoveCallback(const MouseEventCallback& callback);
    void setMousePressCallback(const MouseEventCallback& callback);
    void setMouseReleaseCallback(const MouseEventCallback& callback);
    void setResizeCallback(const ResizeEventCallback& callback);
    void setKeyEventCallback(const KeyEventCallback& callback);

protected:
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    MouseEventCallback mouseMoveCallback_;
    MouseEventCallback mousePressCallback_;
    MouseEventCallback mouseReleaseCallback_;
    ResizeEventCallback resizeCallback_;
    KeyEventCallback keyEventCallback_;
};
NS_CC_END

#endif // EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP
