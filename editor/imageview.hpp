#ifndef EE_EDITOR_IMAGE_VIEW_HPP
#define EE_EDITOR_IMAGE_VIEW_HPP

#include <QOpenGLWidget>

namespace cocos2d {
class Texture2D;
class Rect;
class Vec2;
} // namespace cocos2d

namespace ee {
class ImageView : public QOpenGLWidget {
private:
    using Self = ImageView;
    using Super = QOpenGLWidget;

public:
    explicit ImageView(QWidget* parent = nullptr);

    virtual ~ImageView() override;

    void clearDisplay();
    void setImagePath(const QString& path);
    void setSpriteFrameName(const QString& name);
    void setBlendFunc(GLenum src, GLenum dst);
    void setBlendStraightAlpha();
    void setBlendPremultipliedAlpha();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

    void clearBackground();
    void displayImage(const QString& imagePath);
    void displaySpriteFrame(const QString& spriteFrameName);
    void displayTexture(const cocos2d::Texture2D* texture,
                        const cocos2d::Rect& rect, const cocos2d::Vec2& offset,
                        bool rotated);

private:
    enum class Display { None, Image, SpriteFrame };

    Display display_;
    QString imagePath_;
    QString spriteFrameName_;
    GLenum blendSrc_;
    GLenum blendDst_;
};
} // namespace ee

#endif // EE_EDITOR_IMAGE_VIEW_HPP
