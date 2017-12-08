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
template <class ValueT>
class Property {
public:
    using Value = ValueT;

    using Reader = std::function<Value(const cocos2d::Node* node)>;
    using Writer = std::function<bool(cocos2d::Node* node, const Value& value)>;

    explicit Property(const std::string& name, const Reader& reader,
                      const Writer& writer)
        : name_(name)
        , reader_(reader)
        , writer_(writer) {}

    const std::string& getName() const { return name_; }
    const Reader& getReader() const { return reader_; }
    const Writer& getWriter() const { return writer_; }

    std::optional<Value> read(const cocos2d::Node* node) const {
        return getReader()(node);
    }

    bool write(cocos2d::Node* node, const Value& value) const {
        return getWriter()(node, value);
    }

private:
    std::string name_;
    Reader reader_;
    Writer writer_;
};

template <class Target, class Value,
          class Reader = std::function<Value(const Target* node)>>
typename Property<Value>::Reader makePropertyReader(const Reader& reader) {
    return [reader](const cocos2d::Node* node_) {
        auto node = dynamic_cast<const Target*>(node_);
        assert(node != nullptr);
        return reader(node);
    };
}

template <class Target, class Value,
          class Writer = std::function<bool(Target* node, const Value& value)>>
typename Property<Value>::Writer makePropertyWriter(const Writer& writer) {
    return [writer](cocos2d::Node* node_, const Value& value) {
        auto node = dynamic_cast<Target*>(node_);
        if (node == nullptr) {
            assert(false);
            return false;
        }
        writer(node, value);
        return true;
    };
}

template <class Target>
struct PropertyHelper {
    template <class Value, class Reader>
    static auto makeReader(const Reader& reader) {
        return makePropertyReader<Target, Value>(reader);
    }

    template <class Value, class Writer>
    static auto makeWriter(const Writer& writer) {
        return makePropertyWriter<Target, Value>(writer);
    }
};

template <class T>
struct IsProperty : std::false_type {};

template <class T>
struct IsProperty<Property<T>> : std::true_type {};

using PropertyBool = Property<bool>;
using PropertyInt = Property<int>;
using PropertyFloat = Property<float>;
using PropertyString = Property<std::string>;

template <class Enum>
using PropertyEnum = Property<Enum>;

using PropertyBlend = Property<cocos2d::BlendFunc>;
using PropertyColor3B = Property<cocos2d::Color3B>;
using PropertyPoint = Property<cocos2d::Point>;
using PropertyRect = Property<cocos2d::Rect>;
using PropertySize = Property<cocos2d::Size>;
} // namespace ee

#endif // EE_PARSER_PROPERTY_HPP
