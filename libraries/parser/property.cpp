#include <ciso646>

#include "property.hpp"
#include "propertyreader.hpp"
#include "propertywriter.hpp"

#include <base/ccTypes.h>
#include <math/Vec2.h>

namespace ee {
template <class T> using Self = Property<T>;

template <class T>
Self<T>::Property(const std::string& name)
    : name_(name) {}

template <class T> const std::string& Self<T>::name() const {
    return name_;
}

/// bool
template <>
bool Property<bool>::get(const PropertyReader& reader,
                         const bool& defaultValue) const {
    return reader.getBoolProperty(name(), defaultValue);
}

template <>
void Property<bool>::set(PropertyWriter& writer, const bool& value) const {
    writer.setProperty(name(), value);
}

template <>
bool Property<bool>::add(PropertyWriter& writer, const bool& value) const {
    return writer.addProperty(name(), value);
}

/// int
template <>
int Property<int>::get(const PropertyReader& reader,
                       const int& defaultValue) const {
    return reader.getIntProperty(name(), defaultValue);
}

template <>
void Property<int>::set(PropertyWriter& writer, const int& value) const {
    writer.setProperty(name(), value);
}

template <>
bool Property<int>::add(PropertyWriter& writer, const int& value) const {
    return writer.addProperty(name(), value);
}

/// float
template <>
float Property<float>::get(const PropertyReader& reader,
                           const float& defaultValue) const {
    return reader.getFloatProperty(name(), defaultValue);
}

template <>
void Property<float>::set(PropertyWriter& writer, const float& value) const {
    writer.setProperty(name(), value);
}

template <>
bool Property<float>::add(PropertyWriter& writer, const float& value) const {
    return writer.addProperty(name(), value);
}

/// std::string
template <>
std::string Property<std::string>::get(const PropertyReader& reader,
                                       const std::string& defaultValue) const {
    return reader.getStringProperty(name(), defaultValue);
}

template <>
void Property<std::string>::set(PropertyWriter& writer,
                                const std::string& value) const {
    writer.setProperty(name(), value);
}

template <>
bool Property<std::string>::add(PropertyWriter& writer,
                                const std::string& value) const {
    return writer.addProperty(name(), value);
}

/// cocos2d::Point
template <>
cocos2d::Point
Property<cocos2d::Point>::get(const PropertyReader& reader,
                              const cocos2d::Point& defaultValue) const {
    auto nameX = name() + "_x";
    auto nameY = name() + "_y";
    if (not reader.hasProperty(nameX)) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameY)) {
        return defaultValue;
    }
    auto x = reader.getFloatProperty(nameX);
    auto y = reader.getFloatProperty(nameY);
    return cocos2d::Point(x, y);
}

template <>
void Property<cocos2d::Point>::set(PropertyWriter& writer,
                                   const cocos2d::Point& value) const {
    writer.setProperty(name() + "_x", value.x);
    writer.setProperty(name() + "_y", value.y);
}

template <>
bool Property<cocos2d::Point>::add(PropertyWriter& writer,
                                   const cocos2d::Point& value) const {
    if (not writer.addProperty(name() + "_x", value.x)) {
        return false;
    }
    if (not writer.addProperty(name() + "_y", value.y)) {
        return false;
    }
    return true;
}

/// cocos2d::Color3B
template <>
cocos2d::Color3B
Property<cocos2d::Color3B>::get(const PropertyReader& reader,
                                const cocos2d::Color3B& defaultValue) const {
    auto nameR = name() + "_r";
    auto nameG = name() + "_g";
    auto nameB = name() + "_b";
    if (not reader.hasProperty(nameR)) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameG)) {
        return defaultValue;
    }
    if (not reader.hasProperty(nameB)) {
        return defaultValue;
    }
    auto r = static_cast<GLubyte>(reader.getIntProperty(nameR));
    auto g = static_cast<GLubyte>(reader.getIntProperty(nameG));
    auto b = static_cast<GLubyte>(reader.getIntProperty(nameB));
    return cocos2d::Color3B(r, g, b);
}

template <>
void Property<cocos2d::Color3B>::set(PropertyWriter& writer,
                                     const cocos2d::Color3B& value) const {
    writer.setProperty(name() + "_r", value.r);
    writer.setProperty(name() + "_g", value.g);
    writer.setProperty(name() + "_b", value.b);
}

template <>
bool Property<cocos2d::Color3B>::add(PropertyWriter& writer,
                                     const cocos2d::Color3B& value) const {
    if (not writer.addProperty(name() + "_r", value.r)) {
        return false;
    }
    if (not writer.addProperty(name() + "_g", value.g)) {
        return false;
    }
    if (not writer.addProperty(name() + "_b", value.b)) {
        return false;
    }
    return true;
}

template class Property<bool>;
template class Property<int>;
template class Property<float>;
template class Property<std::string>;
template class Property<cocos2d::Point>;
template class Property<cocos2d::Color3B>;
} // namespace ee
