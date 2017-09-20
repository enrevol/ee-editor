#ifndef EE_PARSER_EDITOR_READER_HPP
#define EE_PARSER_EDITOR_READER_HPP

#include <cstddef>
#include <string>

#include "nodeloaderlibrary.hpp"

#include <base/CCValue.h>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class NodeGraph;
class NodeLoaderLibrary;

class EditorReader {
public:
    EditorReader(const NodeLoaderLibrary& library);
    ~EditorReader();

    cocos2d::Node* readDictionary(const cocos2d::ValueMap& dict);
    cocos2d::Node* readNodeGraph(const NodeGraph& graph);

private:
    NodeLoaderLibrary loaderLibrary_;
};
} // namespace ee

#endif // EE_PARSER_EDITOR_READER_HPP
