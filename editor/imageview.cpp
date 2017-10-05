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
    displayTexture(texture, rect, cocos2d::Vec2::ZERO, false);
}

void Self::displaySpriteFrame(const QString& spriteFrameName) {
    auto cache = cocos2d::SpriteFrameCache::getInstance();
    auto spriteFrame =
        cache->getSpriteFrameByName(spriteFrameName.toStdString());
    auto texture = spriteFrame->getTexture();
    auto&& rect = spriteFrame->getRect();
    auto&& offset = spriteFrame->getOffset();
    auto rotated = spriteFrame->isRotated();
    displayTexture(texture, rect, offset, rotated);
}

void Self::displayTexture(const cocos2d::Texture2D* texture,
                          const cocos2d::Rect& rect,
                          const cocos2d::Vec2& offset, bool rotated) {
    auto f = getGLFunctions(this);

    auto screenWidth = size().width();
    auto screenHeight = size().height();

    auto textureWidth = texture->getContentSize().width;
    auto textureHeight = texture->getContentSize().height;

    // Without rotation.
    auto frameRect = rect;
    if (rotated) {
        std::swap(frameRect.size.width, frameRect.size.height);
    }

    auto viewWidth = rect.size.width + std::abs(offset.x) * 2;
    auto viewHeight = rect.size.height + std::abs(offset.y) * 2;

    auto scaleX = screenWidth / viewWidth;
    auto scaleY = screenHeight / viewHeight;

    // Keep aspect ratio.
    auto scale = std::min(scaleX, scaleY);
    screenWidth /= scale;
    screenHeight /= scale;

    auto paddingX = (screenWidth - viewWidth) / 2;
    auto paddingY = (screenHeight - viewHeight) / 2;

    f->glMatrixMode(GL_PROJECTION);
    f->glLoadIdentity();
    f->glOrtho(0, screenWidth, screenHeight, 0, 0, 1);

    f->glEnable(GL_BLEND);
    f->glBlendFunc(blendSrc_, blendDst_);

    f->glEnable(GL_TEXTURE_2D);
    f->glBindTexture(GL_TEXTURE_2D, texture->getName());

    f->glBegin(GL_QUADS);

    Q_ASSERT(0 <= frameRect.getMinX() && frameRect.getMaxX() <= textureWidth);
    Q_ASSERT(0 <= frameRect.getMinY() && frameRect.getMaxY() <= textureHeight);

    cocos2d::Rect texRect(frameRect.getMinX() / textureWidth,
                          frameRect.getMinY() / textureHeight,
                          frameRect.size.width / textureWidth,
                          frameRect.size.height / textureHeight);

    // y-axis is reversed (texture coordinate): from top to bottom.
    cocos2d::Rect vertRect(paddingX + offset.x + std::abs(offset.x),
                           paddingY - offset.y + std::abs(offset.y),
                           rect.size.width, rect.size.height);

    auto tex0 = [&] { f->glTexCoord2f(texRect.getMinX(), texRect.getMinY()); };
    auto tex1 = [&] { f->glTexCoord2f(texRect.getMinX(), texRect.getMaxY()); };
    auto tex2 = [&] { f->glTexCoord2f(texRect.getMaxX(), texRect.getMaxY()); };
    auto tex3 = [&] { f->glTexCoord2f(texRect.getMaxX(), texRect.getMinY()); };

    auto vert0 = [&] { f->glVertex2f(vertRect.getMinX(), vertRect.getMinY()); };
    auto vert1 = [&] { f->glVertex2f(vertRect.getMinX(), vertRect.getMaxY()); };
    auto vert2 = [&] { f->glVertex2f(vertRect.getMaxX(), vertRect.getMaxY()); };
    auto vert3 = [&] { f->glVertex2f(vertRect.getMaxX(), vertRect.getMinY()); };

    auto draw = [](auto&& tex, auto&& vert) {
        tex();
        vert();
    };

    if (rotated) {
        draw(tex3, vert0);
        draw(tex0, vert1);
        draw(tex1, vert2);
        draw(tex2, vert3);
    } else {
        draw(tex0, vert0);
        draw(tex1, vert1);
        draw(tex2, vert2);
        draw(tex3, vert3);
    }

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
