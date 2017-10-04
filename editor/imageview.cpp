#include "imageview.hpp"

#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions_2_1>

namespace ee {
using Self = ImageView;

Self::ImageView(QWidget* parent)
    : Super(parent) {}

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
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (imagePath_.isEmpty()) {
        return;
    }

    auto director = cocos2d::Director::getInstance();
    auto textureCache = director->getTextureCache();
    auto texture = textureCache->getTextureForKey(imagePath_.toStdString());
    Q_ASSERT(texture != nullptr);

    f->glEnable(GL_TEXTURE_2D);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_BLEND);
    f->glBindTexture(GL_TEXTURE_2D, texture->getName());

    f->glBegin(GL_QUADS);

    auto invert = [](float y) { return 1.0f - y; };

    // Bottom-left.
    f->glTexCoord2f(0, invert(0));
    f->glVertex2f(-1, -1);

    // Top-left.
    f->glTexCoord2f(0, invert(1));
    f->glVertex2f(-1, 1);

    // Top-right.
    f->glTexCoord2f(1, invert(1));
    f->glVertex2f(1, 1);

    // Bottom-right.
    f->glTexCoord2f(1, invert(0));
    f->glVertex2f(1, -1);

    f->glEnd();

    f->glDisable(GL_TEXTURE_2D);
    f->glDisable(GL_DEPTH_TEST);
    f->glDisable(GL_BLEND);

    GLenum error;
    if ((error = f->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error = " << error;
    }
}

void Self::resizeGL(int w, int h) {
    qDebug() << QString::asprintf("resize image view: width = %d height = %d",
                                  w, h);
    auto f = context()->versionFunctions<QOpenGLFunctions_2_1>();
    f->glViewport(0, 0, w, w);
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
} // namespace ee
