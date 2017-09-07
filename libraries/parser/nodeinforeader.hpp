#ifndef EE_PARSER_NODE_INFO_READER_HPP
#define EE_PARSER_NODE_INFO_READER_HPP

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeInfo;

class NodeInfoReader {
public:
    explicit NodeInfoReader(const cocos2d::Node* node);

    bool readBool(const std::string& name, bool defaultValue) const;
    int readInt(const std::string& name, int defaultValue) const;
    float readFloat(const std::string& name, float defaultValue) const;
    std::string readString(const std::string& name,
                           const std::string& defaultValue) const;

private:
    const NodeInfo* getInfo() const;
    const cocos2d::ValueMap& getDict() const;

    const cocos2d::Node* node_;
};
} // namespace ee

#endif // EE_PARSER_NODE_INFO_READER_HPP
