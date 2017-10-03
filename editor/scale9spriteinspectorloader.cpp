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

QVector<InspectorGroup*> Self::createInspectors() const {
    auto inspectors = Super::createInspectors();
    inspectors.append(new Scale9SpriteInspector());
    return inspectors;
}

QString Self::getClassName() const {
    return QString::fromStdString(Scale9SpriteLoader::ClassName);
}
} // namespace ee
