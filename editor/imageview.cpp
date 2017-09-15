#include "imageview.hpp"

#include <QResizeEvent>

namespace ee {
using Self = ImageView;

Self::ImageView(QWidget* parent)
    : Super(parent) {
    setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void Self::setImagePath(const QString& path) {
    setPixmapKeepAspect(QPixmap(path));
}

void Self::resizeEvent(QResizeEvent* event) {
    Super::resizeEvent(event);
    if (pixmap() == nullptr) {
        return;
    }
    if (pixmap()->isNull()) {
        return;
    }
    setPixmapKeepAspect(*pixmap());
}

void Self::setPixmapKeepAspect(const QPixmap& pixmap) {
    setPixmap(pixmap.scaled(width(), height(), Qt::KeepAspectRatio));
}
} // namespace ee
