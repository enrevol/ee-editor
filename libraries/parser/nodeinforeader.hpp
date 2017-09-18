#ifndef EE_PARSER_NODE_INFO_READER_HPP
#define EE_PARSER_NODE_INFO_READER_HPP

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeInfo;

/// Reads user object in nodes.
class NodeInfoReader final {
public:
    /// Constructs a node info reader bound to the specified node.
    /// @param node The desired node.
    explicit NodeInfoReader(const cocos2d::Node* node);

    /// Reads a bool.
    /// @param name The property name.
    /// @param defaultValue The default value to return if the key doesn't
    /// exist.
    bool readBool(const std::string& name, bool defaultValue) const;

    /// Reads an integer.
    /// @param name The property name.
    /// @param defaultValue The default value to return if the key doesn't
    /// exist.
    int readInt(const std::string& name, int defaultValue) const;

    /// Reads a float.
    /// @param name The property name.
    /// @param defaultValue The default value to return if the key doesn't
    /// exist.
    float readFloat(const std::string& name, float defaultValue) const;

    /// Reads a string.
    /// @param name The property name.
    /// @param defaultValue The default value to return if the key doesn't
    /// exist.
    std::string readString(const std::string& name,
                           const std::string& defaultValue) const;

private:
    const NodeInfo* getInfo() const;
    const cocos2d::ValueMap& getDict() const;

    const cocos2d::Node* node_;
};
} // namespace ee

#endif // EE_PARSER_NODE_INFO_READER_HPP
