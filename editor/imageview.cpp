#include "imageview.hpp"

#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#include <renderer/CCGLProgram.h>
#include <renderer/CCTextureCache.h>
#include <renderer/ccGLStateCache.h>

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFunctions_2_1>

namespace ee {
using Self = ImageView;

Self::ImageView(QWidget* parent)
    : Super(parent) {}

Self::~ImageView() {
    if (sprite_ != nullptr) {
        sprite_->release();
        sprite_ = nullptr;
    }
}

void Self::initializeGL() {
    Super::initializeGL();
    qDebug() << QString::asprintf(
        "initializeGL: context %p sharedContext %p",
        static_cast<const void*>(context()),
        static_cast<const void*>(context()->shareContext()));
    auto f = context()->versionFunctions<QOpenGLFunctions_2_1>();
    f->glGenBuffers(2, buffers_);
    f->glClearColor(50.0f / 255.0f, 50.0f / 255.0f, 50.0f / 255.0f, 1.0f);
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_BLEND);
}

void Self::paintGL() {
    auto f = context()->versionFunctions<QOpenGLFunctions_2_1>();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (sprite_ == nullptr) {
        return;
    }

    auto director = cocos2d::Director::getInstance();
    auto textureCache = director->getTextureCache();
    auto texture = textureCache->getTextureForKey(imagePath_.toStdString());
    Q_ASSERT(texture != nullptr);

    f->glEnable(GL_TEXTURE_2D);
    f->glBindTexture(GL_TEXTURE_2D, texture->getName());
    f->glBegin(GL_QUADS);
    f->glTexCoord2f(0, 0);
    f->glVertex2f(0, 0);
    f->glTexCoord2f(0, 1);
    f->glVertex2f(0, 1);
    f->glTexCoord2f(1, 1);
    f->glVertex2f(1, 1);
    f->glTexCoord2f(1, 0);
    f->glVertex2f(1, 0);
    f->glDisable(GL_TEXTURE_2D);
    f->glEnd();

    return;

    for (ssize_t i = 0; i < command_.getIndexCount(); ++i) {
        indices_[i] = command_.getIndices()[i];
    }

    GLenum error;
    if ((error = f->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error = " << error;
    }

    f->glBindBuffer(GL_ARRAY_BUFFER, buffers_[0]);
    f->glBufferData(GL_ARRAY_BUFFER,
                    static_cast<GLsizeiptr>(
                        sizeof(vert_) *
                        static_cast<std::size_t>(command_.getVertexCount())),
                    &vert_, GL_DYNAMIC_DRAW);

    // cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    f->glEnableVertexAttribArray(0); // Position.
    f->glEnableVertexAttribArray(1); // Color.
    f->glEnableVertexAttribArray(2); // TexCoord

    f->glVertexAttribPointer(
        cocos2d::GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE,
        sizeof(vert_),
        reinterpret_cast<GLvoid*>(offsetof(cocos2d::V3F_C4B_T2F, vertices)));
    f->glVertexAttribPointer(
        cocos2d::GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE,
        sizeof(vert_),
        reinterpret_cast<GLvoid*>(offsetof(cocos2d::V3F_C4B_T2F, colors)));
    f->glVertexAttribPointer(
        cocos2d::GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE,
        sizeof(vert_),
        reinterpret_cast<GLvoid*>(offsetof(cocos2d::V3F_C4B_T2F, texCoords)));
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers_[1]);
    f->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                    static_cast<GLsizeiptr>(
                        sizeof(indices_[0]) *
                        static_cast<std::size_t>(command_.getIndexCount())),
                    indices_, GL_STATIC_DRAW);
    command_.useMaterial();
    f->glDrawElements(GL_TRIANGLES,
                      static_cast<GLsizei>(command_.getIndexCount()),
                      GL_UNSIGNED_SHORT,
                      reinterpret_cast<const GLvoid*>(command_.getIndices()));
    f->glBindBuffer(GL_ARRAY_BUFFER, 0);
    f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    if ((error = f->glGetError()) != GL_NO_ERROR) {
        qDebug() << "OpenGL error = " << error;
    }
    return;

    /*
    f->glBindTexture(GL_TEXTURE_2D, texture->getName());
    f->glBegin(GL_QUADS);

    f->glTexCoord2d(0.0, 0.0);
    f->glVertex2d(0.0, 0.0);

    f->glTexCoord2d(1.0, 0.0);
    f->glVertex2d(1.0, 0.0);

    f->glTexCoord2d(1.0, 1.0);
    f->glVertex2d(1.0, 1.0);

    f->glTexCoord2d(0.0, 1.0);
    f->glVertex2d(0.0, 1.0);

    f->glEnd();
    */
}

void Self::resizeGL(int w, int h) {
    qDebug() << QString::asprintf("resize image view: width = %d height = %d",
                                  w, h);
    auto f = context()->versionFunctions<QOpenGLFunctions_2_1>();
    f->glViewport(0, 0, w, h);
}

void Self::setImagePath(const QString& path) {
    if (sprite_ != nullptr) {
        sprite_->release();
        sprite_ = nullptr;
    }

    auto info = QFileInfo(path);
    if (info.suffix() != "png" && info.suffix() != "pvr" &&
        info.suffix() != "pvr.ccz") {
        imagePath_.clear();
    } else {
        qDebug() << "set image path: " << path;
        imagePath_ = path;

        auto director = cocos2d::Director::getInstance();
        auto textureCache = director->getTextureCache();
        auto texture = textureCache->getTextureForKey(imagePath_.toStdString());
        Q_ASSERT(texture != nullptr);

        sprite_ = cocos2d::Sprite::createWithTexture(texture);
        sprite_->retain();
    }
    update();
}
} // namespace ee
