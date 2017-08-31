#ifndef EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP
#define EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP

#include "platform/CCPlatformMacros.h"

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

NS_CC_BEGIN
using MouseEventCallback = std::function<void(QMouseEvent* event)>;
using KeyEventCallback = std::function<void(QKeyEvent* event)>;
using ResizeEventCallback = std::function<void(QResizeEvent* event)>;
using RepaintCallback = std::function<void()>;

/// Inherits from QOpenGLWidget and provides callbacks for mouse and keyboard
/// events.
class CC_DLL OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT

private:
    using Self = OpenGLWidget;
    using Super = QOpenGLWidget;

public:
    explicit OpenGLWidget(QWidget* parent = nullptr);

    virtual ~OpenGLWidget() override;

    /// Sets the repaint interval in milliseconds.
    /// Defaults is 1 / 60 seconds.
    void setRepaintInterval(int milliseconds);

    void setRepaintCallback(const RepaintCallback& callback);
    void setMouseMoveCallback(const MouseEventCallback& callback);
    void setMousePressCallback(const MouseEventCallback& callback);
    void setMouseReleaseCallback(const MouseEventCallback& callback);
    void setKeyPressCallback(const KeyEventCallback& callback);
    void setKeyReleaseCallback(const KeyEventCallback& callback);
    void setResizeCallback(const ResizeEventCallback& callback);

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;

    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    int repaintInterval_;
    QTimer* timer_;

    RepaintCallback repaintCallback_;
    MouseEventCallback mouseMoveCallback_;
    MouseEventCallback mousePressCallback_;
    MouseEventCallback mouseReleaseCallback_;
    KeyEventCallback keyPressCallback_;
    KeyEventCallback keyReleaseCallback_;
    ResizeEventCallback resizeCallback_;
};
NS_CC_END

#endif // EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP
