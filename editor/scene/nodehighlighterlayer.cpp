#include <ciso646>

#include "nodehighlighter.hpp"
#include "nodehighlighterlayer.hpp"

namespace ee {
using Self = NodeHighlighterLayer;

Self::~NodeHighlighterLayer() {}

bool Self::init() {
    if (not Super::init()) {
        return false;
    }
    hoverHighlighter_ = NodeHighlighter::create();
    hoverHighlighter_->hover();
    hoverHighlighter_->setVisible(false);
    addChild(hoverHighlighter_);
    return true;
}

void Self::onEnter() {
    Super::onEnter();
}

void Self::onExit() {
    Super::onExit();
}

void Self::hover(const cocos2d::Node* node) {
    auto region = getRegion(node);
    hoverHighlighter_->setVisible(true);
    hoverHighlighter_->setRegion(region);
}

void Self::unhover() {
    hoverHighlighter_->setVisible(false);
}

void Self::select(const cocos2d::Node* node) {
    auto region = getRegion(node);
    auto highlighter = getOrCreateSelectHighlighter(node);
    highlighter->setVisible(true);
    highlighter->setRegion(region);
}

void Self::deselect(const cocos2d::Node* node) {
    auto highlighter = getOrCreateSelectHighlighter(node);
    highlighter->setVisible(false);
}

void Self::deselectAll() {
    for (auto&& elt : selectHighlighters_) {
        auto&& highlighter = elt.second;
        highlighter->setVisible(false);
    }
}

void Self::clearSelection() {
    for (auto&& elt : selectHighlighters_) {
        auto&& highlighter = elt.second;
        highlighter->removeFromParentAndCleanup(true);
    }
    selectHighlighters_.clear();
}

cocos2d::Rect Self::getRegion(const cocos2d::Node* node) const {
    auto transform =
        node->getNodeToWorldTransform() * getWorldToNodeTransform();
    cocos2d::Rect rect(cocos2d::Point::ZERO, node->getContentSize());
    return cocos2d::RectApplyTransform(rect, transform);
}

NodeHighlighter* Self::getOrCreateSelectHighlighter(const cocos2d::Node* node) {
    auto iter = selectHighlighters_.find(node);
    if (iter == selectHighlighters_.cend()) {
        auto highlighter = NodeHighlighter::create();
        highlighter->select();
        highlighter->setVisible(false);
        addChild(highlighter);
        iter = selectHighlighters_.emplace(node, highlighter).first;
    }
    return iter->second;
}
} // namespace ee
