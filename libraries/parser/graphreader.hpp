#ifndef EE_PARSER_GRAPH_READER_HPP
#define EE_PARSER_GRAPH_READER_HPP

#include <cstddef>
#include <string>

#include "nodeloaderlibrary.hpp"

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeGraph;
class NodeLoaderLibrary;

class GraphReader final {
public:
    GraphReader();
    GraphReader(const NodeLoaderLibrary& library);

    ~GraphReader();

    cocos2d::Node* readDictionary(const cocos2d::ValueMap& dict) const;
    cocos2d::Node* readNodeGraph(const NodeGraph& graph) const;

    void addDefaultProperties(NodeGraph& graph) const;

    const NodeLoaderPtr& getNodeLoader(const NodeGraph& graph) const;

    const NodeLoaderLibrary& getNodeLoaderLibrary() const;

protected:
private:
    NodeLoaderLibrary loaderLibrary_;
};
} // namespace ee

#endif // EE_PARSER_GRAPH_READER_HPP
