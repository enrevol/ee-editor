#include "skeletonanimationinspectorloader.hpp"
#include "skeletonanimationinspector.hpp"

#include <parser/skeletonanimationloader.hpp>

namespace ee {
using Self = SkeletonAnimationInspectorLoader;

InspectorLoaderPtr Self::create() {
    return std::unique_ptr<Self>(new Self());
}

Self::SkeletonAnimationInspectorLoader() {}

Self::~SkeletonAnimationInspectorLoader() {}

Inspector* Self::createInspector() const {
    return new SkeletonAnimationInspector();
}

bool Self::isRoot() const {
    return false;
}

QString Self::getParent() const {
    return QString::fromStdString(NodeLoader::ClassName);
}

QString Self::getName() const {
    return QString::fromStdString(SkeletonAnimationLoader::ClassName);
}
} // namespace ee
