#include "base/ccTypes.h"
#include "platform/CCDevice.h"

#include <QFontDatabase>
#include <QImage>
#include <QPainter>

NS_CC_BEGIN
class BitmapDC {
private:
    using Self = BitmapDC;

public:
    static BitmapDC& getInstance() {
        static Self sharedInstance;
        return sharedInstance;
    }

protected:
    BitmapDC(const Self&) = delete;
    Self& operator=(const Self&) = delete;

    BitmapDC()
        : painter_(nullptr)
        , image_(nullptr) {}

    ~BitmapDC() {
        CC_SAFE_DELETE(painter_);
        CC_SAFE_DELETE(image_);
    }

    bool drawText(const std::string& text, QSize& size,
                  const FontDefinition& textDefinition,
                  const std::string& fontName, int fontSize = 0);

private:
    friend Device;

    QPainter* painter_;
    QImage* image_;
};

bool BitmapDC::drawText(const std::string& text, QSize& size,
                        const FontDefinition& textDefinition,
                        const std::string& fontName, int fontSize) {
    if (text.empty()) {
        return false;
    }
    auto f_ttf = fontName.find(".ttf");
    auto f_TTF = fontName.find(".TTF");
    if (f_ttf != std::string::npos || f_TTF != std::string::npos) {
        QFontDatabase::addApplicationFont(QString::fromStdString(fontName));

        // Remove .ttf suffix.
        auto f_slash = fontName.rfind("/");
        auto f_dot = fontName.rfind(".");
        auto newFontName = fontName.substr(f_slash + 1, f_dot - f_slash - 1);
        return drawText(text, size, textDefinition, fontName, fontSize);
    }

    std::map<TextHAlignment, Qt::AlignmentFlag> hMap;
    hMap[TextHAlignment::CENTER] = Qt::AlignHCenter;
    hMap[TextHAlignment::LEFT] = Qt::AlignLeft;
    hMap[TextHAlignment::RIGHT] = Qt::AlignRight;

    std::map<TextVAlignment, Qt::AlignmentFlag> vMap;
    vMap[TextVAlignment::TOP] = Qt::AlignTop;
    vMap[TextVAlignment::BOTTOM] = Qt::AlignBottom;
    vMap[TextVAlignment::CENTER] = Qt::AlignVCenter;

    int flags = 0;
    flags |= hMap.at(textDefinition._alignment);
    flags |= vMap.at(textDefinition._vertAlignment);

    auto image = new QImage(100, 100, QImage::Format_ARGB32);
    QPainter painter(image);

    QFont font(QString::fromStdString(fontName), fontSize);
    painter.setFont(font);

    QRect rect =
        painter.boundingRect(QRect(), flags, QString::fromStdString(text));

    // If content width is zero, use text size as content size.
    if (size.width() <= 0) {
        size.setWidth(rect.width());
        size.setHeight(rect.height());
    }

    QRect drawRect(0, 0, 0, 0);
    drawRect.setRight(rect.width());
    drawRect.setBottom(rect.height());

    image_ = new QImage(size, QImage::Format_ARGB32);
    painter_ = new QPainter(image_);

    painter_->setCompositionMode(QPainter::CompositionMode_Source);
    painter_->fillRect(drawRect, Qt::transparent);

    painter_->setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter_->setPen(Qt::white);
    painter_->setFont(font);
    painter_->drawText(drawRect, flags, QString::fromStdString(text));
    return true;
}

int Device::getDPI() {
    return 160;
}

void Device::setAccelerometerEnabled(bool enabled) {
    CC_UNUSED_PARAM(enabled);
}

void Device::setAccelerometerInterval(float interval) {
    CC_UNUSED_PARAM(interval);
}

void Device::setKeepScreenOn(bool keepScreenOn) {
    CC_UNUSED_PARAM(keepScreenOn);
}

void Device::vibrate(float duration) {
    CC_UNUSED_PARAM(duration);
}

Data Device::getTextureDataForText(const char* text,
                                   const FontDefinition& textDefinition,
                                   TextAlign align, int& width, int& height,
                                   bool& hasPremultipliedAlpha) {
    if (text == nullptr) {
        return Data::Null;
    }
    auto&& dc = BitmapDC::getInstance();
    QSize size;
    size.setWidth(width);
    size.setHeight(height);

    // Draw the text on the Bitmap DC.
    auto result =
        dc.drawText(text, size, textDefinition, textDefinition._fontName,
                    textDefinition._fontSize);
    if (not result) {
        return Data::Null;
    }

    // FIXME:
    // hasPremultipliedAlpha = ???
    hasPremultipliedAlpha = true;

    auto data = Data::Null;
    auto len = dc.image_->byteCount();
    data.copy(dc.image_->bits(), len);
    return data;
}

NS_CC_END
