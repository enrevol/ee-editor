#include "spriteinspectorloader.hpp"
#include "spriteinspector.hpp"

#include <parser/spriteloader.hpp>

namespace ee {
using Self = SpriteInspectorLoader;

InspectorLoaderPtr Self::create() {
    return std::unique_ptr<Self>(new Self());
}

Self::SpriteInspectorLoader() {}

Self::~SpriteInspectorLoader() {}

Inspector* Self::createInspector() const {
    return new SpriteInspector();
}

bool Self::isRoot() const {
    return false;
}

QString Self::getParent() const {
    return QString::fromStdString(NodeLoader::Name);
}

QString Self::getName() const {
    return QString::fromStdString(SpriteLoader::Name);
}
} // namespace ee
