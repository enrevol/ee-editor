#include "imageview.hpp"

#include <2d/CCSpriteFrameCache.h>
#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions_2_1>

namespace ee {
using Self = ImageView;

auto getGLFunctions(const QOpenGLWidget* widget) {
    return widget->context()->versionFunctions<QOpenGLFunctions_2_1>();
}

Self::ImageView(QWidget* parent)
    : Super(parent) {
    setBlendPremultipliedAlpha();
    clearDisplay();
}

Self::~ImageView() {}

void Self::initializeGL() {
    Super::initializeGL();
    qDebug() << QString::asprintf(
        "initializeGL: context %p sharedContext %p",
        static_cast<const void*>(context()),
        static_cast<const void*>(context()->shareContext()));
    auto f = context()->versionFunctions<QOpenGLFunctions_2_1>();
    constexpr auto color = 50.0f / 255.0f;
    f->glClearColor(color, color, color, 1.0f);
}

void Self::paintGL() {
    clearBackground();
    if (display_ == Display::None) {
        return;
    }
    if (display_ == Display::Image) {
        displayImage(imagePath_);
        return;
    }
    if (display_ == Display::SpriteFrame) {
        displaySpriteFrame(spriteFrameName_);
        return;
    }
    Q_ASSERT(false);
}

void Self::resizeGL(int w, int h) {
    qDebug() << QString::asprintf("resize image view: width = %d height = %d",
                                  w, h);
}

void Self::clearBackground() {
    auto f = getGLFunctions(this);
    f->glClear(GL_COLOR_BUFFER_BIT);
}

void Self::displayImage(const QString& imagePath) {
    auto director = cocos2d::Director::getInstance();
    auto textureCache = director->getTextureCache();
    auto texture = textureCache->getTextureForKey(imagePath.toStdString());
    Q_ASSERT(texture != nullptr);

    cocos2d::Rect rect;
    rect.origin = cocos2d::Point::ZERO;
    rect.size = texture->getContentSize();
    displayTexture(texture, rect);
}

void Self::displaySpriteFrame(const QString& spriteFrameName) {
    auto cache = cocos2d::SpriteFrameCache::getInstance();
    auto spriteFrame =
        cache->getSpriteFrameByName(spriteFrameName.toStdString());
    auto texture = spriteFrame->getTexture();
    auto&& rect = spriteFrame->getRect();
    displayTexture(texture, rect);
}

void Self::displayTexture(const cocos2d::Texture2D* texture,
                          const cocos2d::Rect& rect) {
    auto f = getGLFunctions(this);

    auto width = size().width();
    auto height = size().height();

    auto textureWidth = texture->getContentSize().width;
    auto textureHeight = texture->getContentSize().height;

    auto scaleX = width / rect.size.width;
    auto scaleY = height / rect.size.height;

    // Keep aspect ratio.
    auto scale = std::min(scaleX, scaleY);
    width /= scale;
    height /= scale;

    auto paddingX = (width - rect.size.width) / 2;
    auto paddingY = (height - rect.size.height) / 2;

    f->glMatrixMode(GL_PROJECTION);
    f->glLoadIdentity();
    f->glOrtho(0, width, height, 0, 0, 1);

    f->glEnable(GL_BLEND);
    f->glBlendFunc(blendSrc_, blendDst_);

    f->glEnable(GL_TEXTURE_2D);
    f->glBindTexture(GL_TEXTURE_2D, texture->getName());

    f->glBegin(GL_QUADS);

    Q_ASSERT(0 <= rect.getMinX() && rect.getMaxX() <= textureWidth);
    Q_ASSERT(0 <= rect.getMinY() && rect.getMaxY() <= textureHeight);

    // Bottom-left.
    f->glTexCoord2f(rect.getMinX() / textureWidth,
                    rect.getMinY() / textureHeight);
    f->glVertex2f(paddingX, paddingY);

    // Top-left.
    f->glTexCoord2f(rect.getMinX() / textureWidth,
                    rect.getMaxY() / textureHeight);
    f->glVertex2f(paddingX, height - paddingY);

    // Top-right.
    f->glTexCoord2f(rect.getMaxX() / textureWidth,
                    rect.getMaxY() / textureHeight);
    f->glVertex2f(width - paddingX, height - paddingY);

    // Bottom-right.
    f->glTexCoord2f(rect.getMaxX() / textureWidth,
                    rect.getMinY() / textureHeight);
    f->glVertex2f(width - paddingX, paddingY);

    f->glEnd();

    f->glDisable(GL_TEXTURE_2D);
    f->glDisable(GL_BLEND);

    GLenum error;
    if ((error = f->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error = " << error;
    }
}

void Self::clearDisplay() {
    display_ = Display::None;
    update();
}

void Self::setImagePath(const QString& path) {
    qDebug() << "Image view set image path: " << path;
    display_ = Display::Image;
    imagePath_ = path;
    update();
}

void Self::setSpriteFrameName(const QString& name) {
    qDebug() << "Image view set sprite frame name: " << name;
    display_ = Display::SpriteFrame;
    spriteFrameName_ = name;
    update();
}

void Self::setBlendFunc(GLenum src, GLenum dst) {
    qDebug() << "Image view set blend mode: " << src << ' ' << dst;
    blendSrc_ = src;
    blendDst_ = dst;
    update();
}

void Self::setBlendStraightAlpha() {
    setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Self::setBlendPremultipliedAlpha() {
    setBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}
} // namespace ee
