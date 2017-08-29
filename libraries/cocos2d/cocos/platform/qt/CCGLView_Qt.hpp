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

    void mouseMove(QMouseEvent* event);
    void mousePress(QMouseEvent* event);
    void mouseRelease(QMouseEvent* event);
    void keyPress(QKeyEvent* event);
    void keyRelease(QKeyEvent* event);

protected:
    GLViewImpl();

private:
    virtual bool initWithView(OpenGLWidget* view);

    bool captured_;
    float frameZoomFactor_;
    float screenScaleFactor_;

    std::vector<Touch*> touches_;
    Touch* touch_;
    OpenGLWidget* view_;
};
NS_CC_END

#endif // EE_EDITOR_CC_GL_VIEW_QT_HPP
