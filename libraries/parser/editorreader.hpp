#ifndef EE_PARSER_EDITOR_READER_HPP
#define EE_PARSER_EDITOR_READER_HPP

#include <string>

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
enum class Property {
    Int,
    Float,

};

class EditorReader {
public:
    Reader();

    cocos2d::Node* readNodeGraph(const cocos2d::ValueMap& graph);
};
} // namespace ee

#endif // EE_PARSER_EDITOR_READER_HPP
