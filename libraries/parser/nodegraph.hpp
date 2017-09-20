#ifndef EE_PARSER_NODE_GRAPH_HPP
#define EE_PARSER_NODE_GRAPH_HPP

#include <base/CCValue.h>

namespace ee {
class PropertyHandler;

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

    void setProperty(const std::string& name, const cocos2d::Value& value);
    void setProperty(const std::string& name, bool value);
    void setProperty(const std::string& name, int value);
    void setProperty(const std::string& name, float value);
    void setProperty(const std::string& name, const std::string& value);

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
