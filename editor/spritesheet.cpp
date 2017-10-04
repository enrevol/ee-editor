#include "spritesheet.hpp"
#include "utils.hpp"

#include <qtplist/plistparser.h>

#include <QBuffer>
#include <QJsonObject>

namespace ee {
using Self = SpriteSheet;

Self::SpriteSheet(const QString& content) {
    auto array = content.toUtf8();
    QBuffer buffer(&array);
    auto variant = PListParser::parsePList(&buffer);
    auto json = QJsonValue::fromVariant(variant);

    auto dict = json.toObject();
    auto frames = dict.value("frames").toObject();
    for (auto&& frame : frames.keys()) {
        frames_.append(frame);
    }
}

const QVector<QString>& Self::getFrames() const {
    return frames_;
}
} // namespace ee
