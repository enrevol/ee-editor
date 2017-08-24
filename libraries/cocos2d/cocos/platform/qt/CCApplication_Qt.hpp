#ifndef EE_EDITOR_CC_APPLICATION_QT_HPP
#define EE_EDITOR_CC_APPLICATION_QT_HPP

#include <string>

#include "platform/CCApplicationProtocol.h"
#include "platform/CCCommon.h"

#include <QApplication>

NS_CC_BEGIN
class CC_DLL Application : public QApplication, public ApplicationProtocol {
    Q_OBJECT

private:
    using Self = Application;
    using Super = QApplication;

public:
    Application(int argc, char* argv[]);

    virtual ~Application() override;

    virtual void setAnimationInterval(float interval) override;

    /// Run the message loop.
    int run();

    /// Get current application instance.
    /// @return Current application instance pointer.
    static Application* getInstance();

    virtual LanguageType getCurrentLanguage() override;

    virtual const char* getCurrentLanguageCode() override;

    virtual Platform getTargetPlatform() override;

    virtual std::string getVersion() override;

    virtual bool openURL(const std::string& url) override;

public Q_SLOTS:
    void timerUpdate();

protected:
    static Self* sharedApplication_;

    /// micro second.
    long animationInterval_;

private:
    QTimer* timer_;
    int referenceCount_;
};
NS_CC_END

#endif // EE_EDITOR_CC_APPLICATION_QT_HPP
