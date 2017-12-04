#include "graphreader.hpp"
#include "nodegraph.hpp"
#include "nodeinfo.hpp"
#include "nodeloader.hpp"
#include "propertyhandler.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = GraphReader;

Self::GraphReader() {
    loaderLibrary_.addDefaultLoaders();
}

Self::GraphReader(const NodeLoaderLibrary& library)
    : loaderLibrary_(library) {}

Self::~GraphReader() {}

cocos2d::Node* Self::readDictionary(const ValueMap& dict) const {
    return readNodeGraph(NodeGraph(dict));
}

cocos2d::Node* Self::readNodeGraph(const NodeGraph& graph) const {
    auto&& loader = getNodeLoader(graph);
    auto node = loader->createNode();
    node->setUserObject(NodeInfo::create());
    auto&& propertyHandler = graph.getPropertyHandler();
    loader->loadProperties(node, propertyHandler);
    for (auto&& child : graph.getChildren()) {
        auto childNode = readNodeGraph(child);
        node->addChild(childNode);
    }
    return node;
}

void Self::addDefaultProperties(NodeGraph& graph) const {
    // FIXME.
    /*
    auto&& loader = getNodeLoader(graph);
    auto&& defaultProperties =
        loader->getDefaultPropertyReader().getProperties();
    auto&& propertyReader = graph.getPropertyReader();
    auto&& propertyWriter = graph.getPropertyWriter();
    for (auto&& elt : defaultProperties) {
        auto&& key = elt.first;
        if (propertyReader.hasProperty(key)) {
            continue;
        }
        auto&& value = elt.second;
        propertyWriter.setProperty(key, value);
    }
    for (auto&& child : graph.getChildren()) {
        addDefaultProperties(child);
    }
    */
}

const NodeLoaderPtr& Self::getNodeLoader(const NodeGraph& graph) const {
    auto baseClass = graph.getBaseClass();
    auto customClass = graph.getCustomClass();
    auto className = (customClass.empty() ? baseClass : customClass);
    auto&& loader = loaderLibrary_.getLoader(className);
    return loader;
}

const NodeLoaderLibrary& Self::getNodeLoaderLibrary() const {
    return loaderLibrary_;
}
} // namespace ee
