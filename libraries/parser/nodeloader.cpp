#include "nodeloader.hpp"
#include "propertyhandler.hpp"

#include <2d/CCNode.h>

namespace ee {
namespace property {
constexpr auto position_x = "position_x";
constexpr auto position_y = "position_y";
constexpr auto content_size_width = "content_size_width";
constexpr auto content_size_height = "content_size_height";
} // namespace property

using Self = NodeLoader;

Self::NodeLoader(cocos2d::Node* node)
    : node_(node) {

    auto&& handler = getPropertyHandler();
    handler->addWriteFloatHandler(property::content_size_width,
                                  [this](float value) {
                                      auto size = getNode()->getContentSize();
                                      size.width = value;
                                      getNode()->setContentSize(size);
                                  });
    handler->addWriteFloatHandler(property::content_size_height,
                                  [this](float value) {
                                      auto size = getNode()->getContentSize();
                                      size.height = value;
                                      getNode()->setContentSize(size);
                                  });
    handler->addWriteFloatHandler(property::position_x, [this](float value) {
        auto position = getNode()->getPosition();
        position.x = value;
        getNode()->setPosition(position);
    });
    handler->addWriteFloatHandler(property::position_y, [this](float value) {
        auto position = getNode()->getPosition();
        position.y = value;
        getNode()->setPosition(position);
    });
    handler->addReadFloatHandler(property::content_size_width, [this] {
        return getNode()->getContentSize().width;
    });
    handler->addReadFloatHandler(property::content_size_height, [this] {
        return getNode()->getContentSize().height;
    });
    handler->addReadFloatHandler(property::position_x,
                                 [this] { return getNode()->getPosition().x; });
    handler->addReadFloatHandler(property::position_y,
                                 [this] { return getNode()->getPosition().y; });
}

Self::~NodeLoader() {}

cocos2d::Node* Self::getNode() {
    return node_;
}
} // namespace ee
