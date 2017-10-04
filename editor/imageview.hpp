#ifndef EE_EDITOR_IMAGE_VIEW_HPP
#define EE_EDITOR_IMAGE_VIEW_HPP

#include <base/ccTypes.h>
#include <platform/CCGL.h>
#include <renderer/CCTrianglesCommand.h>

#include <QOpenGLWidget>

namespace cocos2d {
class Sprite;
} // namespace cocos2d

namespace ee {
class ImageView : public QOpenGLWidget {
private:
    using Self = ImageView;
    using Super = QOpenGLWidget;

public:
    explicit ImageView(QWidget* parent = nullptr);

    virtual ~ImageView() override;

    void setImagePath(const QString& path);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

private:
    QString imagePath_;

    cocos2d::TrianglesCommand command_;
    cocos2d::V3F_C4B_T2F vert_;
    GLushort indices_[100];
    GLuint buffers_[2];

    cocos2d::Sprite* sprite_;
};
} // namespace ee

#endif // EE_EDITOR_IMAGE_VIEW_HPP
