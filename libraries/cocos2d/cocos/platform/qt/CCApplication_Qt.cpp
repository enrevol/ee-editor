#include <algorithm>

#include "base/CCDirector.h"
#include "math/CCGeometry.h"
#include "platform/CCFileUtils.h"
#include "platform/CCPlatformConfig.h"
#include "platform/qt/CCApplication_Qt.hpp"

#include <QTimer>

NS_CC_BEGIN
using Self = Application;

Self* Self::sharedApplication_ = nullptr;

Self::Application(int argc, char* argv[])
    : Super(argc, argv)
    , animationInterval_(1.0f / 60.0f * 1000.0f) {
    qDebug() << __PRETTY_FUNCTION__;
    timer_ = nullptr;
    referenceCount_ = 0;
    CC_ASSERT(sharedApplication_ == nullptr);
    sharedApplication_ = this;
}

Self::~Application() {
    qDebug() << __PRETTY_FUNCTION__;
    CC_ASSERT(this == sharedApplication_);
    sharedApplication_ = nullptr;
}

int Self::run() {
    qDebug() << __PRETTY_FUNCTION__;
    if (not applicationDidFinishLaunching()) {
        return 0;
    }

    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &Self::timerUpdate);
    timer_->start(animationInterval_);

    return getInstance()->exec();
}

void Self::setAnimationInterval(float interval) {
    animationInterval_ = interval * 1000.0f;
    if (timer_ != nullptr) {
        timer_->start(animationInterval_);
    }
}

Self::Platform Self::getTargetPlatform() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    return Platform::OS_MAC;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    return Platform::OS_WINDOWS;
#else
    static_assert(false, "Platform not supported");
#endif
}

std::string Self::getVersion() {
    return "";
}

Self* Self::getInstance() {
    CC_ASSERT(sharedApplication_ != nullptr);
    return sharedApplication_;
}

const char* Self::getCurrentLanguageCode() {
    return QLocale::system().name().toStdString().c_str();
}

LanguageType Self::getCurrentLanguage() {
    switch (QLocale::system().language()) {
    case QLocale::Chinese:
        return LanguageType::CHINESE;
    case QLocale::English:
        return LanguageType::ENGLISH;
    case QLocale::France:
        return LanguageType::FRENCH;
    }

    // FIXME
    /*
    if ([languageCode isEqualToString:@"it"])
        return LanguageType::ITALIAN;
    if ([languageCode isEqualToString:@"de"])
        return LanguageType::GERMAN;
    if ([languageCode isEqualToString:@"es"])
        return LanguageType::SPANISH;
    if ([languageCode isEqualToString:@"nl"])
        return LanguageType::DUTCH;
    if ([languageCode isEqualToString:@"ru"])
        return LanguageType::RUSSIAN;
    if ([languageCode isEqualToString:@"ko"])
        return LanguageType::KOREAN;
    if ([languageCode isEqualToString:@"ja"])
        return LanguageType::JAPANESE;
    if ([languageCode isEqualToString:@"hu"])
        return LanguageType::HUNGARIAN;
    if ([languageCode isEqualToString:@"pt"])
        return LanguageType::PORTUGUESE;
    if ([languageCode isEqualToString:@"ar"])
        return LanguageType::ARABIC;
    if ([languageCode isEqualToString:@"nb"])
        return LanguageType::NORWEGIAN;
    if ([languageCode isEqualToString:@"pl"])
        return LanguageType::POLISH;
    if ([languageCode isEqualToString:@"tr"])
        return LanguageType::TURKISH;
    if ([languageCode isEqualToString:@"uk"])
        return LanguageType::UKRAINIAN;
    if ([languageCode isEqualToString:@"ro"])
        return LanguageType::ROMANIAN;
    if ([languageCode isEqualToString:@"bg"])
        return LanguageType::BULGARIAN;
        */
    return LanguageType::ENGLISH;
}

bool Self::openURL(const std::string& url) {
    // FIXME.
    // NSString* msg =
    //     [NSString stringWithCString:url.c_str()
    //     encoding:NSUTF8StringEncoding];
    // NSURL* nsUrl = [NSURL URLWithString:msg];
    // return [[NSWorkspace sharedWorkspace] openURL:nsUrl];
    return false;
}

void Self::timerUpdate() {
    // referencecount_ is here to prevent calling the mainloop from nested event
    // loops.
    if (referenceCount_ == 0) {
        Director::getInstance()->mainLoop();
    }
}
NS_CC_END
