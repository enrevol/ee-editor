#ifndef EE_EDITOR_APP_DELEGATE_HPP
#define EE_EDITOR_APP_DELEGATE_HPP

#include "platform/CCApplication.h"

namespace ee {
class AppDelegate : private cocos2d::Application {
private:
    using Self = AppDelegate;
    using Super = cocos2d::Application;

public:
    AppDelegate(int argc, char* argv[]);

    virtual ~AppDelegate() override;

    void setView(QWidget* view);

    virtual bool applicationDidFinishLaunching() override;

    virtual void applicationDidEnterBackground() override;

    virtual void applicationWillEnterForeground() override;

private:
    QWidget* view_;
};
} // namespace ee

#endif // EE_EDITOR_APP_DELEGATE_HPP
