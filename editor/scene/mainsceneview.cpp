#include <ciso646>

#include "config.hpp"
#include "gizmo.hpp"
#include "mainsceneview.hpp"
#include "nodehighlighterlayer.hpp"
#include "rulerview.hpp"
#include "selection/selectionpath.hpp"
#include "selection/selectiontree.hpp"
#include "utils.hpp"

#include <parser/graphreader.hpp>
#include <parser/nodegraph.hpp>
#include <parser/nodeloader.hpp>
#include <parser/nodeloaderlibrary.hpp>
#include <parser/propertyhandler.hpp>

#include <2d/CCLayer.h>
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#include <base/CCEventDispatcher.h>
#include <base/CCEventListenerCustom.h>
#include <base/CCEventListenerMouse.h>
#include <base/CCEventListenerTouch.h>
#include <base/CCRefPtr.h>
#include <base/ccUTF8.h>
#include <platform/qt/CCGLView_Qt.hpp>
#include <renderer/CCGLProgram.h>

#include <QDebug>

namespace ee {
using Self = MainSceneView;

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

    background_ =
        cocos2d::LayerColor::create(cocos2d::Color4B(50, 50, 50, 255));
    addChild(background_, +0);

    rulerView_ = RulerView::create()
                     ->setMinDisplayLength(10.0f)
                     ->setMaxDisplayLength(50.0f)
                     ->setLineWidth(1.0f)
                     ->setUnitLength(1.0f)
                     ->setOrigin(cocos2d::Point::ZERO)
                     ->setRegion(_director->getWinSize());
    addChild(rulerView_, +1);

    originNode_ = cocos2d::Node::create();
    addChild(originNode_, +2);

    highlighter_ = NodeHighlighterLayer::create();
    addChild(highlighter_, +3);

    gizmo_ = Gizmo::create();
    gizmo_->setVisible(false);
    gizmo_->setMovable(false);
    addChild(gizmo_, +4);
    connect(gizmo_, &Gizmo::moveBy, this, &Self::moveSelectionBy);

    selectTree(SelectionTree::emptySelection());

    touchListener_ = cocos2d::EventListenerTouchOneByOne::create();
    touchListener_->onTouchBegan = std::bind(
        &Self::touchBegan, this, std::placeholders::_1, std::placeholders::_2);
    touchListener_->onTouchMoved = std::bind(
        &Self::touchMoved, this, std::placeholders::_1, std::placeholders::_2);
    touchListener_->onTouchEnded = std::bind(
        &Self::touchEnded, this, std::placeholders::_1, std::placeholders::_2);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener_,
                                                                 this);

    mouseListener_ = cocos2d::EventListenerMouse::create();
    mouseListener_->onMouseDown =
        std::bind(&Self::mousePressed, this, std::placeholders::_1);
    mouseListener_->onMouseMove =
        std::bind(&Self::mouseMoved, this, std::placeholders::_1);
    mouseListener_->onMouseUp =
        std::bind(&Self::mouseReleased, this, std::placeholders::_1);
    mouseListener_->onMouseScroll =
        std::bind(&Self::mouseScrolled, this, std::placeholders::_1);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener_,
                                                                 this);

    windowResizedListener_ = cocos2d::EventListenerCustom::create(
        cocos2d::GLViewImpl::EVENT_WINDOW_RESIZED,
        std::bind(&Self::updateWindowSize, this));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(
        windowResizedListener_, this);

    mousePressing_ = false;
    mouseMoved_ = false;

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
    Q_UNUSED(delta);
    updateSelection();
    updateGizmo();
}

void Self::updateSelection() {
    updateSelection(*selection_);
}

void Self::updateSelection(const SelectionTree& selection) {
    highlighter_->deselectAll();
    for (auto&& path : selection.getPaths()) {
        auto node = path.find(rootNode_);
        highlighter_->select(node);
    }
}

void Self::updateGizmo() {
    if (selection_->isEmpty()) {
        gizmo_->setVisible(false);
        gizmo_->setMovable(false);
    } else {
        gizmo_->setVisible(true);
        gizmo_->setMovable(true);
        auto&& path = selection_->getPaths().front();
        auto node = path.find(rootNode_);
        gizmo_->setPosition(
            node->isIgnoreAnchorPointForPosition()
                ? node->convertToWorldSpace(cocos2d::Point::ZERO)
                : node->convertToWorldSpaceAR(cocos2d::Point::ZERO));
    }
}

void Self::setNodeGraph(const NodeGraph& graph) {
    qDebug() << Q_FUNC_INFO;
    nodeGraph_ = std::make_unique<NodeGraph>(graph);

    if (rootNode_ != nullptr) {
        rootNode_->removeFromParentAndCleanup(true);
    }

    auto library = NodeLoaderLibrary();
    library.addDefaultLoaders();

    GraphReader reader(library);
    rootNode_ = reader.readNodeGraph(graph);
    originNode_->addChild(rootNode_);
}

void Self::selectTree(const SelectionTree& selection) {
    qDebug() << Q_FUNC_INFO;
    selection_ = std::make_unique<SelectionTree>(selection);
}

void Self::moveSelectionBy(const cocos2d::Vec2& delta) {
    constexpr auto eps = std::numeric_limits<float>::epsilon();
    if (std::abs(delta.x) <= eps && std::abs(delta.y) <= eps) {
        return;
    }
    qDebug() << QString::asprintf("move gizmo by (%f, %f)",
                                  static_cast<double>(delta.x),
                                  static_cast<double>(delta.y));
    Q_ASSERT(not selection_->isEmpty());
    auto&& paths = selection_->getPaths();
    for (auto&& path : paths) {
        auto node = path.find(rootNode_);
        auto worldPosition =
            node->isIgnoreAnchorPointForPosition()
                ? node->convertToWorldSpace(cocos2d::Point::ZERO)
                : node->convertToWorldSpaceAR(cocos2d::Point::ZERO);
        auto newWorldPosition = worldPosition + delta;
        Q_ASSERT(node->getParent() != nullptr);
        auto newPosition =
            node->getParent()->convertToNodeSpace(newWorldPosition);
        node->setPosition(newPosition);
        /*
        Q_EMIT propertyValueChanged(
            path,
            QString::fromStdString(NodeLoader::Property::Position.nameX()),
            cocos2d::Value(newPosition.x));
        Q_EMIT propertyValueChanged(
            path,
            QString::fromStdString(NodeLoader::Property::Position.nameY()),
            cocos2d::Value(newPosition.y));
            */
    }
}

/*
void Self::updateSelectionProperty(const NodeGraph& graph,
                                   const SelectionPath& path,
                                   const QString& propertyName,
                                   const cocos2d::Value& value) {
    qDebug() << "Root scene: update property " << propertyName << " = "
             << QString::fromStdString(value.asString());
    Q_ASSERT(not path.isEmpty());
    NodeLoaderLibrary library;
    library.addDefaultLoaders();
    GraphReader reader(library);
    auto node = path.find(rootNode_);
    auto subGraph = path.find(graph);
    updateSelectionProperty(node, reader.getNodeLoader(subGraph), propertyName,
                            value);
}

void Self::updateSelectionProperty(cocos2d::Node* node,
                                   const NodeLoaderPtr& nodeLoader,
                                   const QString& propertyName,
                                   const cocos2d::Value& value) {
    auto&& propertyHandler = nodeLoader->getPropertyHandler();
    propertyHandler.writeProperty(node, propertyName.toStdString(), value);
}
*/

bool Self::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    Q_UNUSED(touch);
    Q_UNUSED(event);
    return false;
}

void Self::touchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    Q_UNUSED(touch);
    Q_UNUSED(event);
}

void Self::touchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    Q_UNUSED(touch);
    Q_UNUSED(event);
}

namespace {
cocos2d::Node*
doRecursively(cocos2d::Node* node,
              const std::function<bool(cocos2d::Node* node)>& f) {
    for (auto&& child : node->getChildren()) {
        auto handler = doRecursively(child, f);
        if (handler != nullptr) {
            return handler;
        }
    }
    if (f(node)) {
        return node;
    }
    return nullptr;
}

cocos2d::Node* findCapturedNode(cocos2d::Node* rootNode,
                                const cocos2d::Point& position) {
    return doRecursively(rootNode, [position](cocos2d::Node* node) {
        auto box = cocos2d::Rect(0, 0, node->getContentSize().width,
                                 node->getContentSize().height);
        auto localPosition = node->convertToNodeSpace(position);
        return box.containsPoint(localPosition);
    });
}
} // namespace

void Self::mousePressed(cocos2d::EventMouse* event) {
    auto&& position = event->getLocation();
    mousePressing_ = true;
    mouseMoved_ = false;
}

void Self::mouseMoved(cocos2d::EventMouse* event) {
    mouseMoved_ = true;
    auto&& position = event->getLocation();
    if (mousePressing_) {
        highlighter_->unhover();
        // FIXME.

        if (event->getMouseButton() ==
            cocos2d::EventMouse::MouseButton::BUTTON_MIDDLE) {
            auto&& delta = event->getDelta();
            auto origin = originNode_->getPosition();
            origin += delta;
            originNode_->setPosition(origin);
            rulerView_->setOrigin(origin);
        }
    } else {
        if (rootNode_ != nullptr) {
            auto capturedNode = findCapturedNode(rootNode_, position);
            if (capturedNode == nullptr) {
                highlighter_->unhover();
            } else {
                highlighter_->hover(capturedNode);
            }
        }
    }
}

void Self::mouseReleased(cocos2d::EventMouse* event) {
    Q_ASSERT(mousePressing_);
    mousePressing_ = false;
    auto&& position = event->getLocation();
    if (mouseMoved_) {
        // FIXME.
    } else {
        if (rootNode_ != nullptr) {
            auto selection = SelectionTree::emptySelection();
            auto capturedNode = findCapturedNode(rootNode_, position);
            if (capturedNode != nullptr) {
                auto path = SelectionPath::fromNode(capturedNode, rootNode_);
                selection.addPath(path);
            }
            if (selection != *selection_) {
                selectTree(selection);
                Q_EMIT selectionTreeChanged(selection);
            }
        }
    }
}

void Self::mouseScrolled(cocos2d::EventMouse* event) {
    auto&& mousePosition = event->getLocation();
    auto offset = mousePosition - originNode_->getPosition();
    float multiplier = 1.0f;
    if (event->getScrollY() > 0) {
        multiplier += 0.2f;
    } else {
        multiplier -= 0.2f;
    }
    auto originScale = originNode_->getScale() * multiplier;
    if (0.05f <= originScale && originScale <= 500.0f) {
        auto originPosition = mousePosition - offset * multiplier;
        originNode_->setScale(originScale);
        originNode_->setPosition(originPosition);
        rulerView_->setUnitLength(originScale)->setOrigin(originPosition);
    }
}

void Self::updateWindowSize() {
    auto&& winSize = _director->getWinSize();
    background_->setContentSize(winSize);
    rulerView_->setRegion(winSize);
}
} // namespace ee
