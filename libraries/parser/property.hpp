#ifndef EE_PARSER_PROPERTY_HPP
#define EE_PARSER_PROPERTY_HPP

#include <string>

namespace cocos2d {
class Vec2;
using Point = Vec2;
struct Color3B;
class Size;
} // namespace cocos2d

namespace ee {
class PropertyHandler;
class PropertyReader;
class PropertyWriter;

class PropertyBase {
public:
    void addReadHandler(PropertyHandler& handler) const;
    void addWriterHandler(PropertyHandler& handler) const;
};

template <class T> class Property : public PropertyBase {
public:
    using Value = T;

    Property(const std::string& name);

    const std::string& name() const;

    Value get(const PropertyReader& reader, const Value& defaultValue) const;
    void set(PropertyWriter& writer, const Value& value) const;
    bool add(PropertyWriter& writer, const Value& value) const;

private:
    std::string name_;
};

template <class T> struct IsProperty : std::false_type {};
template <class T> struct IsProperty<Property<T>> : std::true_type {};

using BoolProperty = Property<bool>;
using IntProperty = Property<int>;
using FloatProperty = Property<float>;
using StringProperty = Property<std::string>;
using PointProperty = Property<cocos2d::Point>;
using SizeProperty = Property<cocos2d::Size>;
using ColorProperty = Property<cocos2d::Color3B>;
} // namespace ee

#endif // EE_PARSER_PROPERTY_HPP
