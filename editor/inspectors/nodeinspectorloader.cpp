#include "nodeinspectorloader.hpp"
#include "nodeinspector.hpp"

#include <parser/nodeloader.hpp>

namespace ee {
using Self = NodeInspectorLoader;

InspectorLoaderPtr Self::create() {
    return std::unique_ptr<Self>(new Self());
}

Self::NodeInspectorLoader() {}

Self::~NodeInspectorLoader() {}

Inspector* Self::createInspector() const {
    return new NodeInspector();
}

bool Self::isRoot() const {
    return true;
}

QString Self::getParent() const {
    return "___";
}

QString Self::getName() const {
    return QString::fromStdString(NodeLoader::Name);
}
} // namespace ee
