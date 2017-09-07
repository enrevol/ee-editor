#ifndef EE_PARSER_NODE_INFO_WRITER_HPP
#define EE_PARSER_NODE_INFO_WRITER_HPP

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeInfo;

class NodeInfoWriter {
public:
    explicit NodeInfoWriter(cocos2d::Node* node);

    void writeBool(const std::string& name, bool value);
    void writeInt(const std::string& name, int value);
    void writeFloat(const std::string& name, float value);
    void writeString(const std::string& name, const std::string& value);

private:
    NodeInfo* getInfo();
    cocos2d::ValueMap& getDict();

    cocos2d::Node* node_;
};
} // namespace ee

#endif // EE_PARSER_NODE_INFO_WRITER_HPP
