#ifndef EE_PARSER_GRAPH_READER_HPP
#define EE_PARSER_GRAPH_READER_HPP

#include <cstddef>
#include <string>

#include "nodeloaderlibrary.hpp"
#include "value.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeGraph;
class NodeLoaderLibrary;

/// Build node graph.
class GraphReader final {
public:
    /// Constructs an empty graph reader (no loader library).
    GraphReader();

    /// Constructs a graph reader with the specified loader library.
    /// @param library The desired loader library.
    GraphReader(const NodeLoaderLibrary& library);

    ~GraphReader();

    cocos2d::Node* readDictionary(const ValueMap& dict) const;
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
