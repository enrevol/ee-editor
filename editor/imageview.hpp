#ifndef EE_EDITOR_IMAGE_VIEW_HPP
#define EE_EDITOR_IMAGE_VIEW_HPP

#include <QLabel>

namespace ee {
class ImageView : public QLabel {
    Q_OBJECT

private:
    using Self = ImageView;
    using Super = QLabel;

public:
    explicit ImageView(QWidget* parent = nullptr);

    void setImagePath(const QString& path);

private:
    virtual void resizeEvent(QResizeEvent* event) override;

    void setPixmapKeepAspect(const QPixmap& pixmap);
};
} // namespace ee

#endif // EE_EDITOR_IMAGE_VIEW_HPP
