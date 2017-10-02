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

QVector<InspectorGroup*> Self::createInspectors() const {
    auto inspectors = Super::createInspectors();
    inspectors.append(new SpriteInspector());
    return inspectors;
}

QString Self::getClassName() const {
    return QString::fromStdString(SpriteLoader::ClassName);
}
} // namespace ee
