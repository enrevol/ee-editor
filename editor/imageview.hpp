#ifndef EE_EDITOR_IMAGE_VIEW_HPP
#define EE_EDITOR_IMAGE_VIEW_HPP

#include <QOpenGLWidget>

namespace ee {
class ImageView : public QOpenGLWidget {
private:
    using Self = ImageView;
    using Super = QOpenGLWidget;

public:
    explicit ImageView(QWidget* parent = nullptr);

    virtual ~ImageView() override;

    void setImagePath(const QString& path);
    void setBlendFunc(GLenum src, GLenum dst);
    void setBlendStraightAlpha();
    void setBlendPremultipliedAlpha();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

private:
    QString imagePath_;
    GLenum blendSrc_;
    GLenum blendDst_;
};
} // namespace ee

#endif // EE_EDITOR_IMAGE_VIEW_HPP
