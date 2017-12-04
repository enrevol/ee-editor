#ifndef EE_PARSER_PROPERTY_HPP
#define EE_PARSER_PROPERTY_HPP

#include <functional>

#include "value.hpp"

namespace cocos2d {
struct BlendFunc;
struct Color3B;
class Node;
class Vec2;
using Point = Vec2;
class Rect;
class Size;
} // namespace cocos2d

namespace ee {
class PropertyHandler;
class PropertyReader;
class PropertyWriter;

/// SFINAE whether the specified class is a property.
template <class T>
struct IsProperty;

/// A node property.
template <class TargetT, class ValueT>
class Property {
public:
    using Target = TargetT;
    using Value = ValueT;

    using Reader = std::function<Value(const Target* node)>;
    using Writer = std::function<void(Target* node, const Value& value)>;

    explicit Property(const std::string& name, const Reader& reader,
                      const Writer& writer)
        : name_(name)
        , reader_(reader)
        , writer_(writer) {}

    const std::string& getName() const { return name_; }

    Value read(const Target* node) const { return reader_(node); }

    void write(Target* node, const Value& value) const { writer_(node, value); }

private:
    std::string name_;
    Reader reader_;
    Writer writer_;
};

template <class T>
struct IsProperty : std::false_type {};

template <class T, class U>
struct IsProperty<Property<T, U>> : std::true_type {};

template <class Target>
using PropertyBool = Property<Target, bool>;

template <class Target>
using PropertyInt = Property<Target, int>;

template <class Target>
using PropertyFloat = Property<Target, float>;

template <class Target>
using PropertyString = Property<Target, std::string>;

template <class Target, class Enum>
using PropertyEnum = Property<Target, Enum>;

template <class Target>
using PropertyBlend = Property<Target, cocos2d::BlendFunc>;

template <class Target>
using PropertyColor3B = Property<Target, cocos2d::Color3B>;

template <class Target>
using PropertyPoint = Property<Target, cocos2d::Point>;

template <class Target>
using PropertyRect = Property<Target, cocos2d::Rect>;

template <class Target>
using PropertySize = Property<Target, cocos2d::Size>;
} // namespace ee

#endif // EE_PARSER_PROPERTY_HPP
