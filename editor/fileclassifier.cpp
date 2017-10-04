#include "fileclassifier.hpp"

namespace ee {
using Self = FileClassifier;

Self::FileClassifier(const QString& path)
    : info_(path) {}

Self::FileClassifier(const QFileInfo& info)
    : info_(info) {}

bool Self::isImage() const {
    return info_.suffix() == "png" || info_.suffix() == "pvr" ||
           info_.completeSuffix() == "pvr.ccz";
}
bool Self::isSpriteSheet() const {
    return info_.suffix() == "plist";
}

bool Self::isInterface() const {
    return info_.suffix() == "json";
}
} // namespace ee
