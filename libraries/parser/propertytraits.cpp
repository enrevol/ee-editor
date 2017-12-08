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
std::optional<bool> Self<bool>::getProperty(const PropertyHandler& handler,
                                            const std::string& name) {
    auto&& value = handler.getProperty(name);
    return map(value, std::mem_fn(&Value::getBool));
}

template <>
void Self<bool>::setProperty(PropertyHandler& handler, const std::string& name,
                             const bool& value) {
    handler.setProperty(name, Value(value));
}

template <>
std::optional<int> Self<int>::getProperty(const PropertyHandler& handler,
                                          const std::string& name) {
    auto&& value = handler.getProperty(name);
    return map(value, std::mem_fn(&Value::getInt));
}

template <>
void Self<int>::setProperty(PropertyHandler& handler, const std::string& name,
                            const int& value) {
    handler.setProperty(name, Value(value));
}

template <>
std::optional<float> Self<float>::getProperty(const PropertyHandler& handler,
                                              const std::string& name) {
    auto&& value = handler.getProperty(name);
    return map(value, std::mem_fn(&Value::getFloat));
}

template <>
void Self<float>::setProperty(PropertyHandler& handler, const std::string& name,
                              const float& value) {
    handler.setProperty(name, Value(value));
}

template <>
std::optional<std::string>
Self<std::string>::getProperty(const PropertyHandler& handler,
                               const std::string& name) {
    auto&& value = handler.getProperty(name);
    return map(value, std::mem_fn(&Value::getString));
}

template <>
void Self<std::string>::setProperty(PropertyHandler& handler,
                                    const std::string& name,
                                    const std::string& value) {
    handler.setProperty(name, Value(value));
}

template <>
std::optional<cocos2d::BlendFunc>
Self<cocos2d::BlendFunc>::getProperty(const PropertyHandler& handler,
                                      const std::string& name) {
    auto src = handler.getProperty<int>(name + "_src");
    return map(src, [&](int src_) {
        auto dst = handler.getProperty<int>(name + "_dst");
        return map(dst, [&](int dst_) {
            cocos2d::BlendFunc blend;
            blend.src = static_cast<GLenum>(src_);
            blend.dst = static_cast<GLenum>(dst_);
            return std::make_optional(blend);
        });
    });
}

template <>
void Self<cocos2d::BlendFunc>::setProperty(PropertyHandler& handler,
                                           const std::string& name,
                                           const cocos2d::BlendFunc& value) {
    handler.setProperty(name + "_src", Value(static_cast<int>(value.src)));
    handler.setProperty(name + "_dst", Value(static_cast<int>(value.dst)));
}

template <>
std::optional<cocos2d::Color3B>
Self<cocos2d::Color3B>::getProperty(const PropertyHandler& handler,
                                    const std::string& name) {
    auto r = handler.getProperty<int>(name + "_r");
    return map(r, [&](int r_) {
        auto g = handler.getProperty<int>(name + "_g");
        return map(g, [&](int g_) {
            auto b = handler.getProperty<int>(name + "_b");
            return map(b, [&](int b_) {
                return std::make_optional(
                    cocos2d::Color3B(static_cast<GLubyte>(r_), //
                                     static_cast<GLubyte>(g_), //
                                     static_cast<GLubyte>(b_)));
            });
        });
    });
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
std::optional<cocos2d::Point>
Self<cocos2d::Point>::getProperty(const PropertyHandler& handler,
                                  const std::string& name) {
    auto x = handler.getProperty<float>(name + " _x");
    return map(x, [&](float x_) {
        auto y = handler.getProperty<float>(name + "_y");
        return map(y, [&](float y_) { //
            return std::make_optional(cocos2d::Point(x_, y_));
        });
    });
}

template <>
void Self<cocos2d::Point>::setProperty(PropertyHandler& handler,
                                       const std::string& name,
                                       const cocos2d::Point& value) {
    handler.setProperty(name + "_x", Value(value.x));
    handler.setProperty(name + "_y", Value(value.y));
}

template <>
std::optional<cocos2d::Rect>
Self<cocos2d::Rect>::getProperty(const PropertyHandler& handler,
                                 const std::string& name) {
    auto x = handler.getProperty<float>(name + "_x");
    return map(x, [&](float x_) {
        auto y = handler.getProperty<float>(name + "_y");
        return map(y, [&](float y_) {
            auto w = handler.getProperty<float>(name + "_width");
            return map(w, [&](float w_) {
                auto h = handler.getProperty<float>(name + "_height");
                return map(h, [&](float h_) { //
                    return std::make_optional(cocos2d::Rect(x_, y_, w_, h_));
                });
            });
        });
    });
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
std::optional<cocos2d::Size>
Self<cocos2d::Size>::getProperty(const PropertyHandler& handler,
                                 const std::string& name) {
    auto w = handler.getProperty<float>(name + "_width");
    return map(w, [&](float w_) {
        auto h = handler.getProperty<float>(name + "_height");
        return map(h, [&](float h_) { //
            return std::make_optional(cocos2d::Size(w_, h_));
        });
    });
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
