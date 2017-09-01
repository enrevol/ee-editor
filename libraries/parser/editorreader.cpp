#include "editorreader.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = EditorReader;

Self::EditorReader() {}
Self::~EditorReader() {}

cocos2d::Node* Self::readNodeGraph(const cocos2d::ValueMap& graph) {
    auto node = cocos2d::Node::create();
    auto&& childrenGraph = graph.at("children").asValueVector();
    for (const cocos2d::Value& v : childrenGraph) {
        assert(v.getType() == cocos2d::Value::Type::MAP);
        auto child = readNodeGraph(v.asValueMap());
        node->addChild(child);
    }
}
} // namespace ee
