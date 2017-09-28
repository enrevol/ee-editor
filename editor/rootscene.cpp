#include <ciso646>

#include "config.hpp"
#include "gizmo.hpp"
#include "rootscene.hpp"
#include "selectionpath.hpp"
#include "selectiontree.hpp"
#include "utils.hpp"

#include <parser/graphreader.hpp>
#include <parser/nodegraph.hpp>
#include <parser/nodeloader.hpp>
#include <parser/nodeloaderlibrary.hpp>
#include <parser/propertyhandler.hpp>

#include <2d/CCLayer.h>
#include <2d/CCSprite.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerMouse.h>
#include <base/CCEventListenerTouch.h>
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

    gizmo_ = Gizmo::create();
    gizmo_->setVisible(false);
    addChild(gizmo_, +1);
    connect(gizmo_, &Gizmo::moveBy, this, &Self::moveSelectionBy);

    setSelection(SelectionTree::emptySelection());

    background_ =
        cocos2d::LayerColor::create(cocos2d::Color4B(50, 50, 50, 255));
    addChild(background_);

    listener_ = cocos2d::EventListenerTouchOneByOne::create();
    listener_->onTouchBegan = std::bind(
        &Self::touchBegan, this, std::placeholders::_1, std::placeholders::_2);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_,
                                                                 this);

    mouseListener_ = cocos2d::EventListenerMouse::create();
    mouseListener_->onMouseUp = [](cocos2d::EventMouse* event) {
        qDebug() << Q_FUNC_INFO;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener_,
                                                                 this);

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
    updateGizmo();
}

void Self::updateSelection() {
    updateSelection(*selection_);
}

void Self::updateSelection(const SelectionTree& selection) {
    unhighlightNodes();
    std::size_t i = 0;
    for (auto&& path : selection.getPaths()) {
        auto node = path.find(rootNode_);
        ensureHighlighters(i + 1);
        highlightNode(highlighters_.at(i), node);
        ++i;
    }
}

void Self::updateGizmo() {
    if (selection_->isEmpty()) {
        gizmo_->setVisible(false);
    } else {
        gizmo_->setVisible(true);
        auto&& path = selection_->getPaths().front();
        auto node = path.find(rootNode_);
        gizmo_->setPosition(node->convertToWorldSpaceAR(cocos2d::Point::ZERO));
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

void Self::setSelection(const SelectionTree& selection) {
    selection_ = std::make_unique<SelectionTree>(selection);
}

void Self::moveSelectionBy(const cocos2d::Vec2& delta) {
    constexpr auto eps = std::numeric_limits<float>::epsilon();
    if (std::abs(delta.x) <= eps && std::abs(delta.y) <= eps) {
        return;
    }
    Q_ASSERT(not selection_->isEmpty());
    auto&& paths = selection_->getPaths();
    for (auto&& path : paths) {
        auto node = path.find(rootNode_);
        auto worldPosition = node->convertToWorldSpaceAR(cocos2d::Point::ZERO);
        auto newWorldPosition = worldPosition + delta;
        Q_ASSERT(node->getParent() != nullptr);
        auto newPosition =
            node->getParent()->convertToNodeSpace(newWorldPosition);
        node->setPosition(newPosition);
        Q_EMIT propertyValueChanged(
            path, QString::fromStdString(NodeLoader::Property::PositionX),
            cocos2d::Value(newPosition.x));
        Q_EMIT propertyValueChanged(
            path, QString::fromStdString(NodeLoader::Property::PositionY),
            cocos2d::Value(newPosition.y));
    }
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
        layer->setOpacity(0);
        addChild(layer);
        highlighters_.push_back(layer);
    }
}

void Self::updateSelectionProperty(const NodeGraph& graph,
                                   const SelectionPath& path,
                                   const QString& propertyName,
                                   const cocos2d::Value& value) {
    Q_ASSERT(not path.isEmpty());
    NodeLoaderLibrary library;
    library.addDefaultLoaders();
    GraphReader reader(library);
    auto node = path.find(rootNode_);
    updateSelectionProperty(node, reader.getNodeLoader(graph), propertyName,
                            value);
}

void Self::updateSelectionProperty(cocos2d::Node* node,
                                   const NodeLoaderPtr& nodeLoader,
                                   const QString& propertyName,
                                   const cocos2d::Value& value) {
    auto&& propertyHandler = nodeLoader->getPropertyHandler();
    propertyHandler.writeProperty(node, propertyName.toStdString(), value);
}

bool Self::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    qDebug() << Q_FUNC_INFO;
    return false;
}
} // namespace ee
