#ifndef EE_EDITOR_CC_GL_VIEW_QT_HPP
#define EE_EDITOR_CC_GL_VIEW_QT_HPP

#include <vector>

#include "math/CCGeometry.h"
#include "platform/CCCommon.h"
#include "platform/CCGLView.h"
#include "platform/CCStdC.h"

#include <QMouseEvent>
#include <QWidget>

NS_CC_BEGIN
class OpenGLWidget;

/// Wraps a QOpenGLWidget and inherits from cocos2d::GLView.
class CC_DLL GLViewImpl : public GLView {
private:
    using Self = GLViewImpl;
    using Super = GLView;

public:
    static const std::string EVENT_WINDOW_RESIZED;

    static Self* create(OpenGLWidget* view);

    virtual ~GLViewImpl() override;

    virtual void end() override;
    virtual bool isOpenGLReady() override;
    virtual void swapBuffers() override;
    virtual void setFrameSize(float width, float height) override;
    virtual void setIMEKeyboardState(bool open) override;
    virtual void setViewName(const std::string& viewName) override;

    virtual void setFrameZoomFactor(float zoomFactor) override;
    virtual float getFrameZoomFactor() const override;

    virtual void setViewPortInPoints(float x, float y, float w,
                                     float h) override;

    virtual void setScissorInPoints(float x, float y, float w,
                                    float h) override;

    virtual QOpenGLContext* getOpenGLContext() const override;

    virtual void setRepaintInterval(int milliseconds) override;

protected:
    GLViewImpl();

    void mouseMove(QMouseEvent* event);
    void mousePress(QMouseEvent* event);
    void mouseRelease(QMouseEvent* event);
    void wheel(QWheelEvent* event);
    void keyPress(QKeyEvent* event);
    void keyRelease(QKeyEvent* event);
    void paint();
    void resize(QResizeEvent* event);

private:
    virtual bool initWithView(OpenGLWidget* view);

    void resizeFrame(float width, float height);

    cocos2d::Point parseCursorPosition(float x, float y) const;
    cocos2d::Point parseCursorPosition(const QPointF& p) const;

    bool touchCaptured_;
    cocos2d::Point previousCursorPosition_;
    OpenGLWidget* view_;
};
NS_CC_END

#endif // EE_EDITOR_CC_GL_VIEW_QT_HPP
