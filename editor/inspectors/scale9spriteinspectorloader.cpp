#include "scale9spriteinspectorloader.hpp"
#include "scale9spriteinspector.hpp"

#include <parser/scale9spriteloader.hpp>

namespace ee {
using Self = Scale9SpriteInspectorLoader;

InspectorLoaderPtr Self::create() {
    return std::unique_ptr<Self>(new Self());
}

Self::Scale9SpriteInspectorLoader() {}

Self::~Scale9SpriteInspectorLoader() {}

Inspector* Self::createInspector() const {
    return new Scale9SpriteInspector();
}

bool Self::isRoot() const {
    return false;
}

QString Self::getParent() const {
    return QString::fromStdString(SpriteLoader::Name);
}

QString Self::getName() const {
    return QString::fromStdString(Scale9SpriteLoader::Name);
}
} // namespace ee
