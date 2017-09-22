#include <ciso646>

#include "config.hpp"
#include "rootscene.hpp"
#include "sceneselection.hpp"
#include "utils.hpp"

#include <parser/graphreader.hpp>
#include <parser/nodegraph.hpp>
#include <parser/nodeloader.hpp>
#include <parser/nodeloaderlibrary.hpp>
#include <parser/propertyhandler.hpp>

#include <2d/CCLayer.h>
#include <2d/CCSprite.h>
#include <base/CCRefPtr.h>
#include <renderer/CCGLProgram.h>

#include <QDebug>

namespace ee {
using Self = RootScene;

Self* Self::create() {
    auto result = new Self();
    result->init();
    result->autorelease();
    return result;
}

bool Self::init() {
    if (not Super::init()) {
        return false;
    }

    selection_ =
        std::make_unique<SceneSelection>(SceneSelection::emptySelection());

    background_ = cocos2d::LayerColor::create(cocos2d::Color4B::BLACK);
    addChild(background_);

    scheduleUpdate();

    return true;
}

void Self::onEnter() {
    Super::onEnter();
}

void Self::onEnterTransitionDidFinish() {
    Super::onEnterTransitionDidFinish();
}

void Self::onExitTransitionDidStart() {
    Super::onExitTransitionDidStart();
}

void Self::onExit() {
    Super::onExit();
}

void Self::update(float delta) {
    updateSelection();
}

void Self::updateSelection() {
    updateSelection(*selection_);
}

void Self::updateSelection(const SceneSelection& selection) {
    unhighlightNodes();
    if (selection.isEmpty()) {
        // Nothing.
    } else if (selection.isRoot()) {
        ensureHighlighters(1);
        highlightNode(highlighters_.front(), rootNode_);
    } else {
        std::size_t i = 0;
        for (auto&& childIndex : selection.getChildrenIndices()) {
            auto treeIndices = selection.getAncestorIndices();
            treeIndices.append(childIndex);
            auto node = getNode(treeIndices);
            ensureHighlighters(i + 1);
            highlightNode(highlighters_.at(i), node);
            ++i;
        }
    }
}

void Self::setNodeGraph(const NodeGraph& graph) {
    nodeGraph_ = std::make_unique<NodeGraph>(graph);

    if (rootNode_ != nullptr) {
        rootNode_->removeFromParentAndCleanup(true);
    }

    auto library = NodeLoaderLibrary();
    library.addDefaultLoaders();

    GraphReader reader(library);
    rootNode_ = reader.readNodeGraph(graph);
    addChild(rootNode_);
}

void Self::setSelection(const SceneSelection& selection) {
    selection_ = std::make_unique<SceneSelection>(selection);
}

void Self::highlightNodes(const std::vector<cocos2d::Node*>& nodes) {
    for (auto i = nodes.size(); i < highlighters_.size(); ++i) {
        unhighlightNode(highlighters_.at(i));
    }
}

void Self::highlightNode(cocos2d::LayerColor* highlighter,
                         const cocos2d::Node* node) {
    highlighter->setVisible(true);

    auto transform = node->getNodeToWorldTransform();
    cocos2d::Rect rect(cocos2d::Point::ZERO, node->getContentSize());
    auto worldRect = cocos2d::RectApplyTransform(rect, transform);
    highlighter->setPosition(worldRect.origin);
    highlighter->setContentSize(worldRect.size);
}

void Self::unhighlightNodes() {
    for (auto&& highlighter : highlighters_) {
        unhighlightNode(highlighter);
    }
}

void Self::unhighlightNode(cocos2d::LayerColor* highlighter) {
    highlighter->setVisible(false);
}

void Self::ensureHighlighters(std::size_t size) {
    for (std::size_t i = highlighters_.size(); i < size; ++i) {
        auto layer = cocos2d::LayerColor::create(cocos2d::Color4B::BLACK);
        layer->setLocalZOrder(+999);
        layer->setOpacity(200);
        addChild(layer);
        highlighters_.push_back(layer);
    }
}

cocos2d::Node* Self::getNode(const QVector<int>& treeIndices) {
    Q_ASSERT(not treeIndices.empty());
    if (treeIndices.isEmpty()) {
        return rootNode_;
    }
    auto node = rootNode_;
    for (auto&& index : treeIndices) {
        node = node->getChildren().at(index);
    }
    return node;
}

void Self::updateProperty(const NodeGraph& graph,
                          const SceneSelection& selection,
                          const QString& propertyName,
                          const cocos2d::Value& value) {
    Q_ASSERT(not selection.isEmpty());
    NodeLoaderLibrary library;
    library.addDefaultLoaders();
    GraphReader reader(library);
    if (selection.isRoot()) {
        updateProperty(rootNode_, reader.getNodeLoader(graph), propertyName,
                       value);
    } else {
        auto parentGraph = &graph;
        auto parentNode = rootNode_;
        for (auto&& index : selection.getAncestorIndices()) {
            parentGraph =
                &parentGraph->getChild(static_cast<std::size_t>(index));
            parentNode = parentNode->getChildren().at(index);
        }
        for (auto&& childIndex : selection.getChildrenIndices()) {
            auto&& childGraph =
                parentGraph->getChild(static_cast<std::size_t>(childIndex));
            auto childNode = parentNode->getChildren().at(childIndex);
            updateProperty(childNode, reader.getNodeLoader(childGraph),
                           propertyName, value);
        }
    }
}

void Self::updateProperty(cocos2d::Node* node, const NodeLoaderPtr& nodeLoader,
                          const QString& propertyName,
                          const cocos2d::Value& value) {
    auto&& propertyHandler = nodeLoader->getPropertyHandler();
    propertyHandler.writeProperty(node, propertyName.toStdString(), value);
}
} // namespace ee
