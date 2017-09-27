#ifndef EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP
#define EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP

#include "platform/CCPlatformMacros.h"

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

NS_CC_BEGIN
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

Q_SIGNALS:
    void onPainted();
    void onMouseMoved(QMouseEvent* event);
    void onMousePressed(QMouseEvent* event);
    void onMouseReleased(QMouseEvent* event);
    void onKeyPressed(QKeyEvent* event);
    void onKeyReleased(QKeyEvent* event);
    void onResized(QResizeEvent* event);
    void onWheeled(QWheelEvent* event);

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
    virtual void wheelEvent(QWheelEvent* event) override;

private:
    int repaintInterval_;
    QTimer* timer_;
};
NS_CC_END

#endif // EE_EDITOR_CC_OPEN_GL_WIDGET_QT_HPP
