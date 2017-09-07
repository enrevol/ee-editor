#ifndef EE_PARSER_NODE_GRAPH_HPP
#define EE_PARSER_NODE_GRAPH_HPP

#include <base/CCValue.h>

namespace ee {
class NodeGraph {
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

    /// Gets a generic property.
    /// @param name The property's name.
    cocos2d::Value getProperty(const std::string& name) const;

    /// Gets a generic property.
    /// @param name The property's name.
    /// @param defaultValue The default value of the property if it doesn't
    /// exist.
    cocos2d::Value getProperty(const std::string& name,
                               const cocos2d::Value& defaultValue) const;

    bool getBoolProperty(const std::string& name) const;
    bool getBoolProperty(const std::string& name, bool defaultValue) const;

    int getIntProperty(const std::string& name) const;
    int getIntProperty(const std::string& name, int defaultValue) const;

    float getFloatProperty(const std::string& name) const;
    float getFloatProperty(const std::string& name, float defaultValue) const;

    std::string getStringProperty(const std::string& name) const;
    std::string getStringProperty(const std::string& name,
                                  const std::string& defaultValue) const;

    std::string getBaseClass() const;
    std::string getCustomClass() const;
    std::string getDisplayName() const;

    const std::vector<NodeGraph>& getChildren() const;

    cocos2d::ValueMap toDict() const;

private:
    cocos2d::ValueMap properties_;
    std::vector<NodeGraph> children_;
};
} // namespace ee

#endif // EE_PARSER_NODE_GRAPH_HPP
