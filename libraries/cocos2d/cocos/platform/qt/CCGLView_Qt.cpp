#include "platform/qt/CCGLView_Qt.hpp"
#include "base/CCDirector.h"
#include "base/CCTouch.h"
#include "base/ccUTF8.h"
#include "platform/qt/CCOpenGLWidget_Qt.hpp"

#include <QDesktopWidget>
#include <QVBoxLayout>

NS_CC_BEGIN
using Self = GLViewImpl;

Self* Self::create(const std::string& viewName) {
    CC_UNUSED_PARAM(viewName);
    return create(nullptr);
}

Self* Self::create(QWidget* parent) {
    return createWithWidget(parent);
}

Self* Self::createWithWidget(QWidget* param) {
    if (param == nullptr) {
        return nullptr;
    }
    auto result = new Self();
    if (not result->createInWidget(param)) {
        CC_SAFE_DELETE(result);
    }

    return result;
}

Self* Self::createWithRect(const std::string& viewName, const Rect& rect,
                           float zoomFactor) {
    CC_UNUSED_PARAM(viewName);
    CC_UNUSED_PARAM(rect);
    CC_UNUSED_PARAM(zoomFactor);
    return nullptr;
}

Self* Self::createWithFullScreen(const std::string& viewName) {
    CC_UNUSED_PARAM(viewName);
    return nullptr;
}

Self::GLViewImpl()
    : initialized_(false)
    , captured_(false)
    , frameZoomFactor_(1.0f)
    , screenScaleFactor_(false)
    , touchSupported_(false)
    , windowMode_(GLViewWindowMode::FixSize)
    , touch_(nullptr)
    , window_(nullptr)
    , parentWidget_(nullptr) {}

Self::~GLViewImpl() {
    CC_SAFE_DELETE(touch_);
}

bool Self::initGL() {
    /*
    auto glVersion = glGetString(GL_VERSION);
    auto errorCode = glGetError();

    if (glVersion == nullptr && errorCode != GL_NO_ERROR) {
        auto msg = StringUtils::format("Error: %d", errorCode);
        MessageBox(msg.c_str(), "Get OpenGL version error.");
        return false;
    }

    if (glVersion == nullptr &&
        std::stof(reinterpret_cast<const char*>(glVersion) < 1.5f)) {
        auto msg = StringUtils::format(
            "OpenGL 1.5 or higher is required (your version is %s).",
            glVersion);
        MessageBox(msg.c_str(), "OpenGL version is too old.");
        return false;
    }

    auto glewInitResult = glewInit();
    */
    return true;
}

void Self::destroyGL() {}

bool Self::createInWidget(QWidget* param) {
    if (window_ != nullptr) {
        return false;
    }
    Q_ASSERT(param != nullptr);
    parentWidget_ = param;

    window_ = new OpenGLWidget();

    window_->setMouseMoveCallback(
        std::bind(&Self::mouseMove, this, std::placeholders::_1));

    window_->setMousePressCallback(
        std::bind(&Self::mousePress, this, std::placeholders::_1));

    window_->setMouseReleaseCallback(
        std::bind(&Self::mouseRelease, this, std::placeholders::_1));

    window_->setResizeCallback([this](QResizeEvent* event) {
        window_->resize(event->size().width(), event->size().height());
    });

    window_->makeCurrent();

    auto layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(window_);
    parentWidget_->setLayout(layout);

    if (not initGL()) {
        destroyGL();
    }

    initialized_ = true;
    return true;
}

bool Self::isOpenGLReady() {
    return initialized_;
}

void Self::end() {
    CC_SAFE_DELETE(touch_);
    CC_SAFE_DELETE(window_);
    delete this;
}

void Self::swapBuffers() {
    if (initialized_) {
        window_->makeCurrent();
        // window_->swapBuffer() ??
    }
}

void Self::setIMEKeyboardState(bool open) {
    CC_UNUSED_PARAM(open);
}

void Self::setViewName(const std::string& viewName) {
    Super::setViewName(viewName);
    if (parentWidget_ != nullptr) {
        parentWidget_->setWindowTitle(QString::fromStdString(getViewName()));
    }
}

void Self::resize(int width, int height) {
    if (window_ == nullptr) {
        return;
    }
    if (Director::getInstance()->getOpenGLView() == nullptr) {
        return;
    }
    if (windowMode_ == GLViewWindowMode::FixSize) {
        window_->setFixedSize(width, height);
        parentWidget_->setFixedSize(width, height);
    } else {
        setDesignResolutionSize(width, height, ResolutionPolicy::EXACT_FIT);
    }
}

void Self::setFrameZoomFactor(float zoomFactor) {
    frameZoomFactor_ = zoomFactor;
    resize(_screenSize.width * zoomFactor, _screenSize.height * zoomFactor);
    centerWindow();

    auto director = Director::getInstance();
    director->setProjection(director->getProjection());
}

float Self::getFrameZoomFactor() const {
    return frameZoomFactor_;
}

void Self::setFrameSize(float width, float height) {
    Super::setFrameSize(width, height);
    resize(width, height);
    centerWindow();
}

void Self::centerWindow() {}

void Self::setViewPortInPoints(float x, float y, float w, float h) {
    Super::setViewPortInPoints(x, y, w, h);
}

void Self::setScissorInPoints(float x, float y, float w, float h) {
    Super::setScissorInPoints(x, y, w, h);
}

void Self::mouseMove(QMouseEvent* event) {
    if (touch_ == nullptr) {
        return;
    }

    if (not captured_) {
        return;
    }

    captured_ = true;
    touch_->setTouchInfo(0, static_cast<float>(event->x()) / screenScaleFactor_,
                         static_cast<float>(event->y()) / screenScaleFactor_);

    std::intptr_t id = touch_->getID();
    auto x = touch_->getLocationInView().x;
    auto y = touch_->getLocationInView().y;
    handleTouchesMove(1, &id, &x, &y);
}

void Self::mousePress(QMouseEvent* event) {
    if (touch_ == nullptr) {
        return;
    }

    if (event->button() != Qt::MouseButton::LeftButton) {
        return;
    }

    captured_ = true;
    touch_->setTouchInfo(0, static_cast<float>(event->x()) / screenScaleFactor_,
                         static_cast<float>(event->y()) / screenScaleFactor_);

    touches_.push_back(touch_);
    std::intptr_t id = touch_->getID();
    auto x = touch_->getLocationInView().x;
    auto y = touch_->getLocationInView().y;
    handleTouchesBegin(1, &id, &x, &y);
}

void Self::mouseRelease(QMouseEvent* event) {
    if (touch_ == nullptr) {
        return;
    }

    if (event->button() != Qt::MouseButton::LeftButton) {
        return;
    }

    captured_ = false;
    touch_->setTouchInfo(0, static_cast<float>(event->x()) / screenScaleFactor_,
                         static_cast<float>(event->y()) / screenScaleFactor_);

    std::intptr_t id = touch_->getID();
    auto x = touch_->getLocationInView().x;
    auto y = touch_->getLocationInView().y;
    handleTouchesEnd(1, &id, &x, &y);

    for (auto i = touches_.cbegin(); i != touches_.cend(); ++i) {
        if (*i == touch_) {
            touches_.erase(i);
            break;
        }
    }
}

QWidget* Self::getGLWidget() {
    return window_;
}
NS_CC_END
