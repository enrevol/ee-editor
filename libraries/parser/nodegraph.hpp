#ifndef EE_PARSER_NODE_GRAPH_HPP
#define EE_PARSER_NODE_GRAPH_HPP

#include <base/CCValue.h>

namespace ee {
class PropertyReader;
class PropertyWriter;

class NodeGraph final {
private:
    using Self = NodeGraph;

public:
    /// Constructs an empty node graph.
    NodeGraph();

    /// Constructs a node graph with the specified dictionary.
    /// @param dict Node graph's dictionary.
    explicit NodeGraph(const cocos2d::ValueMap& dict);

    ~NodeGraph();

    /// Sets the node graph's dictionary.
    /// @param dict The desired dictionary.
    void setDictionary(const cocos2d::ValueMap& dict);

    const cocos2d::ValueMap& getProperties() const;

    PropertyReader getPropertyReader() const;
    PropertyWriter getPropertyWriter();

    std::string getBaseClass() const;
    std::string getCustomClass() const;
    std::string getDisplayName() const;

    void setBaseClass(const std::string& name);
    void setCustomClass(const std::string& name);
    void setDisplayName(const std::string& name);

    Self& getChild(std::size_t index);
    const Self& getChild(std::size_t index) const;

    const std::vector<Self>& getChildren() const;

    void addChild(const Self& child);

    cocos2d::ValueMap toDict() const;

private:
    cocos2d::ValueMap properties_;
    std::vector<Self> children_;
};
} // namespace ee

#endif // EE_PARSER_NODE_GRAPH_HPP
