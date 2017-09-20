#include <ciso646>

#include "config.hpp"
#include "rootscene.hpp"
#include "sceneselection.hpp"
#include "utils.hpp"

#include <parser/editorreader.hpp>
#include <parser/nodegraph.hpp>
#include <parser/nodeloader.hpp>
#include <parser/nodeloaderlibrary.hpp>

#include <2d/CCLayer.h>
#include <2d/CCSprite.h>
#include <base/CCRefPtr.h>
#include <renderer/CCGLProgram.h>

#include <QDebug>

namespace ee {
using Self = RootScene;

Self* Self::getInstance() {
    static cocos2d::RefPtr<Self> sharedInstance = create();
    return sharedInstance;
}

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

    QObject::connect(&Config::getInstance(), &Config::interfaceLoaded,
                     [this](const QFileInfo& path) {
                         setNodeGraph(Config::getInstance()
                                          .getInterfaceSettings()
                                          ->getNodeGraph()
                                          .value());
                     });

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
    if (selection.isEmpty()) {
        unhighlightNodes();
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

    auto reader = EditorReader(library);
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
    if (treeIndices.size() == 1) {
        Q_ASSERT(treeIndices.first() == 0);
        return rootNode_;
    }
    auto node = rootNode_;
    for (int i = 1; i < treeIndices.size(); ++i) {
        auto index = treeIndices.at(i);
        node = node->getChildren().at(index);
    }
    return node;
}
} // namespace ee
