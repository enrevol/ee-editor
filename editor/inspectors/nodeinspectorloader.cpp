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

QVector<InspectorGroup*> Self::createInspectors() const {
    QVector<InspectorGroup*> inspectors;
    inspectors.append(new NodeInspector());
    return inspectors;
}

QString Self::getClassName() const {
    return QString::fromStdString(NodeLoader::ClassName);
}
} // namespace ee
