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

enum class GLViewWindowMode {
    FixSize,
    Resizable,
};

class CC_DLL GLViewImpl : public GLView {
private:
    using Self = GLViewImpl;
    using Super = GLView;

public:
    static Self* create(const std::string& viewName);
    static Self* create(QWidget* parent);
    static Self* createWithWidget(QWidget* param = nullptr);
    static Self* createWithRect(const std::string& viewName, const Rect& rect,
                                float zoomFactor);
    static Self* createWithFullScreen(const std::string& viewName);

    GLViewImpl();
    virtual ~GLViewImpl() override;

    virtual void end() override;
    virtual bool isOpenGLReady() override;
    virtual void swapBuffers() override;
    virtual void setFrameSize(float width, float height) override;
    virtual void setIMEKeyboardState(bool open) override;
    virtual void setViewName(const std::string& viewName) override;

    void resize(int width, int height);

    virtual void setFrameZoomFactor(float zoomFactor) override;
    virtual float getFrameZoomFactor() const override;

    void centerWindow();

    virtual void setViewPortInPoints(float x, float y, float w,
                                     float h) override;
    virtual void setScissorInPoints(float x, float y, float w,
                                    float h) override;

    void mouseMove(QMouseEvent* event);
    void mousePress(QMouseEvent* event);
    void mouseRelease(QMouseEvent* event);

    QWidget* getGLWidget();

private:
    virtual bool createInWidget(QWidget* param);

    bool initGL();
    void destroyGL();

    bool initialized_;
    bool captured_;
    bool touchSupported_;
    float frameZoomFactor_;
    float screenScaleFactor_;

    GLViewWindowMode windowMode_;
    std::vector<Touch*> touches_;
    Touch* touch_;
    OpenGLWidget* window_;
    QWidget* parentWidget_;
};
NS_CC_END

#endif // EE_EDITOR_CC_GL_VIEW_QT_HPP
