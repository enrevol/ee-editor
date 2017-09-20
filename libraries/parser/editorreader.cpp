#include "editorreader.hpp"
#include "nodegraph.hpp"
#include "nodeloader.hpp"
#include "propertyhandler.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = EditorReader;

Self::EditorReader(const NodeLoaderLibrary& library)
    : loaderLibrary_(library) {}

Self::~EditorReader() {}

cocos2d::Node* Self::readDictionary(const cocos2d::ValueMap& dict) {
    return readNodeGraph(NodeGraph(dict));
}

cocos2d::Node* Self::readNodeGraph(const NodeGraph& graph) {
    auto baseClass = graph.getBaseClass();
    auto customClass = graph.getCustomClass();
    auto className = (customClass.empty() ? baseClass : customClass);
    auto&& loader = loaderLibrary_.getLoader(className);
    auto node = loader->createNode();
    auto&& propertyHandler = loader->getPropertyHandler();
    for (auto&& elt : graph.getProperties()) {
        auto&& key = elt.first;
        auto&& value = elt.second;
        if (key == "base_class") {
            continue;
        }
        propertyHandler.writeProperty(node, key, value);
    }
    for (auto&& child : graph.getChildren()) {
        auto childNode = readNodeGraph(child);
        node->addChild(childNode);
    }
    return node;
}
} // namespace ee
