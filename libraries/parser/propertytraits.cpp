#include "propertytraits.hpp"
#include "propertyhandler.hpp"

#include <base/ccTypes.h>
#include <math/CCGeometry.h>
#include <math/Vec2.h>

namespace ee {
namespace detail {
template <class T>
using Self = PropertyTraitsNonEnum<T>;

template <>
bool Self<bool>::getProperty(const PropertyHandler& handler,
                             const std::string& name) {
    return handler.getProperty(name).getBool();
}

template <>
void Self<bool>::setProperty(PropertyHandler& handler, const std::string& name,
                             const bool& value) {
    handler.setProperty(name, Value(value));
}

template <>
int Self<int>::getProperty(const PropertyHandler& handler,
                           const std::string& name) {
    return handler.getProperty(name).getInt();
}

template <>
void Self<int>::setProperty(PropertyHandler& handler, const std::string& name,
                            const int& value) {
    handler.setProperty(name, Value(value));
}

template <>
float Self<float>::getProperty(const PropertyHandler& handler,
                               const std::string& name) {
    return handler.getProperty(name).getFloat();
}

template <>
void Self<float>::setProperty(PropertyHandler& handler, const std::string& name,
                              const float& value) {
    handler.setProperty(name, Value(value));
}

template <>
std::string Self<std::string>::getProperty(const PropertyHandler& handler,
                                           const std::string& name) {
    return handler.getProperty(name).getString();
}

template <>
void Self<std::string>::setProperty(PropertyHandler& handler,
                                    const std::string& name,
                                    const std::string& value) {
    handler.setProperty(name, Value(value));
}

template <>
cocos2d::BlendFunc
Self<cocos2d::BlendFunc>::getProperty(const PropertyHandler& handler,
                                      const std::string& name) {
    auto src = static_cast<GLenum>(handler.getProperty(name + "_src").getInt());
    auto dst = static_cast<GLenum>(handler.getProperty(name + "_dst").getInt());
    cocos2d::BlendFunc blend;
    blend.src = src;
    blend.dst = dst;
    return blend;
}

template <>
void Self<cocos2d::BlendFunc>::setProperty(PropertyHandler& handler,
                                           const std::string& name,
                                           const cocos2d::BlendFunc& value) {
    handler.setProperty(name + "_src", Value(static_cast<int>(value.src)));
    handler.setProperty(name + "_dst", Value(static_cast<int>(value.dst)));
}

template <>
cocos2d::Color3B
Self<cocos2d::Color3B>::getProperty(const PropertyHandler& handler,
                                    const std::string& name) {
    auto r = static_cast<GLubyte>(handler.getProperty(name + "_r").getInt());
    auto g = static_cast<GLubyte>(handler.getProperty(name + "_g").getInt());
    auto b = static_cast<GLubyte>(handler.getProperty(name + "_b").getInt());
    return cocos2d::Color3B(r, g, b);
}

template <>
void Self<cocos2d::Color3B>::setProperty(PropertyHandler& handler,
                                         const std::string& name,
                                         const cocos2d::Color3B& value) {
    handler.setProperty(name + "_r", Value(static_cast<int>(value.r)));
    handler.setProperty(name + "_g", Value(static_cast<int>(value.r)));
    handler.setProperty(name + "_b", Value(static_cast<int>(value.r)));
}

template <>
cocos2d::Point Self<cocos2d::Point>::getProperty(const PropertyHandler& handler,
                                                 const std::string& name) {
    auto x = handler.getProperty(name + "_x").getFloat();
    auto y = handler.getProperty(name + "_y").getFloat();
    return cocos2d::Vec2(x, y);
}

template <>
void Self<cocos2d::Point>::setProperty(PropertyHandler& handler,
                                       const std::string& name,
                                       const cocos2d::Point& value) {
    handler.setProperty(name + "_x", Value(value.x));
    handler.setProperty(name + "_y", Value(value.y));
}

template <>
cocos2d::Rect Self<cocos2d::Rect>::getProperty(const PropertyHandler& handler,
                                               const std::string& name) {
    auto x = handler.getProperty(name + "_x").getFloat();
    auto y = handler.getProperty(name + "_y").getFloat();
    auto w = handler.getProperty(name + "_width").getFloat();
    auto h = handler.getProperty(name + "_height").getFloat();
    return cocos2d::Rect(x, y, w, h);
}

template <>
void Self<cocos2d::Rect>::setProperty(PropertyHandler& handler,
                                      const std::string& name,
                                      const cocos2d::Rect& value) {
    handler.setProperty(name + "_x", Value(value.origin.x));
    handler.setProperty(name + "_y", Value(value.origin.y));
    handler.setProperty(name + "_width", Value(value.size.width));
    handler.setProperty(name + "_heght", Value(value.size.height));
}

template <>
cocos2d::Size Self<cocos2d::Size>::getProperty(const PropertyHandler& handler,
                                               const std::string& name) {
    auto w = handler.getProperty(name + "_width").getFloat();
    auto h = handler.getProperty(name + "_height").getFloat();
    return cocos2d::Size(w, h);
}

template <>
void Self<cocos2d::Size>::setProperty(PropertyHandler& handler,
                                      const std::string& name,
                                      const cocos2d::Size& value) {
    handler.setProperty(name + "_width", Value(value.width));
    handler.setProperty(name + "_heght", Value(value.height));
}
} // namespace detail
} // namespace ee
