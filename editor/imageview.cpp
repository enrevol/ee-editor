#include "imageview.hpp"

#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions_2_1>

namespace ee {
using Self = ImageView;

Self::ImageView(QWidget* parent)
    : Super(parent) {
    setBlendPremultipliedAlpha();
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
    auto f = context()->versionFunctions<QOpenGLFunctions_2_1>();
    f->glClear(GL_COLOR_BUFFER_BIT);
    if (imagePath_.isEmpty()) {
        return;
    }

    auto director = cocos2d::Director::getInstance();
    auto textureCache = director->getTextureCache();
    auto texture = textureCache->getTextureForKey(imagePath_.toStdString());
    Q_ASSERT(texture != nullptr);

    auto width = size().width();
    auto height = size().height();

    auto imageWidth = texture->getContentSize().width;
    auto imageHeight = texture->getContentSize().height;

    auto scaleX = width / imageWidth;
    auto scaleY = height / imageHeight;

    // Keep aspect ratio.
    auto scale = std::min(scaleX, scaleY);
    imageWidth *= scale;
    imageHeight *= scale;

    auto paddingX = (width - imageWidth) / 2;
    auto paddingY = (height - imageHeight) / 2;

    f->glMatrixMode(GL_PROJECTION);
    f->glLoadIdentity();
    f->glOrtho(0, width, height, 0, 0, 1);

    f->glEnable(GL_BLEND);
    f->glBlendFunc(blendSrc_, blendDst_);

    f->glEnable(GL_TEXTURE_2D);
    f->glBindTexture(GL_TEXTURE_2D, texture->getName());

    f->glBegin(GL_QUADS);

    // Bottom-left.
    f->glTexCoord2f(0, 0);
    f->glVertex2f(paddingX, paddingY);

    // Top-left.
    f->glTexCoord2f(0, 1);
    f->glVertex2f(paddingX, imageHeight + paddingY);

    // Top-right.
    f->glTexCoord2f(1, 1);
    f->glVertex2f(paddingX + imageWidth, paddingY + imageHeight);

    // Bottom-right.
    f->glTexCoord2f(1, 0);
    f->glVertex2f(paddingX + imageWidth, paddingY);

    f->glEnd();

    f->glDisable(GL_TEXTURE_2D);
    f->glDisable(GL_BLEND);

    GLenum error;
    if ((error = f->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error = " << error;
    }
}

void Self::resizeGL(int w, int h) {
    qDebug() << QString::asprintf("resize image view: width = %d height = %d",
                                  w, h);
}

void Self::setImagePath(const QString& path) {
    auto info = QFileInfo(path);
    if (info.suffix() != "png" && info.suffix() != "pvr" &&
        info.suffix() != "pvr.ccz") {
        imagePath_.clear();
    } else {
        qDebug() << "set image path: " << path;
        imagePath_ = path;
    }
    update();
}

void Self::setBlendFunc(GLenum src, GLenum dst) {
    qDebug() << "Image view blend changed to: " << src << ' ' << dst;
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
