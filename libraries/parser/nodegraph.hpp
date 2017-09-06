#ifndef EE_PARSER_NODE_GRAPH_HPP
#define EE_PARSER_NODE_GRAPH_HPP

#include <base/CCValue.h>

namespace ee {
class NodeGraph {
private:
    using Self = NodeGraph;

public:
    NodeGraph(const cocos2d::ValueMap& dict);
    ~NodeGraph();

    cocos2d::Value getProperty(
        const std::string& name,
        const cocos2d::Value& defaultValue = cocos2d::Value::Null) const;

    bool getBoolProperty(const std::string& name,
                         bool defaultValue = false) const;

    int getIntProperty(const std::string& name, int defaultValue = 0) const;

    float getFloatProperty(const std::string& name,
                           float defaultValue = 0.0f) const;

    std::string
    getStringProperty(const std::string& name,
                      const std::string& defaultValue = std::string()) const;

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
