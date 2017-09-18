#ifndef EE_PARSER_NODE_INFO_WRITER_HPP
#define EE_PARSER_NODE_INFO_WRITER_HPP

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeInfo;

/// Writes user object in nodes.
class NodeInfoWriter final {
public:
    explicit NodeInfoWriter(cocos2d::Node* node);

    /// Writes a bool.
    /// @param name The property name.
    /// @param value The value to write.
    void writeBool(const std::string& name, bool value);

    /// Writes a integer.
    /// @param name The property name.
    /// @param value The value to write.
    void writeInt(const std::string& name, int value);

    /// Writes a float.
    /// @param name The property name.
    /// @param value The value to write.
    void writeFloat(const std::string& name, float value);

    /// Writes a string.
    /// @param name The property name.
    /// @param value The value to write.
    void writeString(const std::string& name, const std::string& value);

private:
    NodeInfo* getInfo();
    cocos2d::ValueMap& getDict();

    cocos2d::Node* node_;
};
} // namespace ee

#endif // EE_PARSER_NODE_INFO_WRITER_HPP
