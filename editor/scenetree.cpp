#include "scenetree.hpp"

#include <2d/CCNode.h>

namespace ee {
using Self = SceneTree;

Self::SceneTree(QWidget* parent)
    : Super(parent)
    , rootNode_(nullptr) {
    //
}

void Self::setRootNode(cocos2d::Node* node) {
    rootNode_ = node;
}
} // namespace ee
