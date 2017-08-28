#ifndef EE_EDITOR_APP_DELEGATE_HPP
#define EE_EDITOR_APP_DELEGATE_HPP

#include "platform/CCApplication.h"

namespace cocos2d {
class OpenGLWidget;
} // namespace cocos2d

namespace ee {
class AppDelegate : public cocos2d::Application {
private:
    using Self = AppDelegate;
    using Super = cocos2d::Application;

public:
    AppDelegate(int argc, char* argv[]);

    virtual ~AppDelegate() override;

    void setOpenGLView(cocos2d::OpenGLWidget* view);

    virtual bool applicationDidFinishLaunching() override;

    virtual void applicationDidEnterBackground() override;

    virtual void applicationWillEnterForeground() override;

private:
    cocos2d::OpenGLWidget* openGLView_;
};
} // namespace ee

#endif // EE_EDITOR_APP_DELEGATE_HPP
