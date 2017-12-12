#ifndef EE_PARSER_NODE_GRAPH_HPP
#define EE_PARSER_NODE_GRAPH_HPP

#include "propertyhandler.hpp"

namespace ee {
class NodeGraph final {
private:
    using Self = NodeGraph;

public:
    /// Constructs an empty node graph.
    NodeGraph();

    /// Constructs a node graph with the specified dictionary.
    /// @param dict Node graph's dictionary.
    explicit NodeGraph(const ValueMap& dict);

    NodeGraph(const Self& other) = default;

    ~NodeGraph();

    /// Sets the node graph's dictionary.
    /// @param dict The desired dictionary.
    void setDictionary(const ValueMap& dict);

    const PropertyHandler& getPropertyHandler() const;

    std::string getBaseClass() const;
    std::string getCustomClass() const;
    std::string getDisplayName() const;

    void setBaseClass(const std::string& name);
    void setCustomClass(const std::string& name);
    void setDisplayName(const std::string& name);

    Self& getChild(std::size_t index);
    const Self& getChild(std::size_t index) const;

    std::vector<Self>& getChildren();
    const std::vector<Self>& getChildren() const;

    void addChild(const Self& child);

    ValueMap toDict() const;

private:
    PropertyHandler propertyHandler_;
    std::vector<Self> children_;
};
} // namespace ee

#endif // EE_PARSER_NODE_GRAPH_HPP
