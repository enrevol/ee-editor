#ifndef EE_PARSER_PROPERTY_HPP
#define EE_PARSER_PROPERTY_HPP

#include <functional>

#include "optional.hpp"
#include "parserfwd.hpp"
#include "value.hpp"

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class PropertyHandler;
class PropertyReader;
class PropertyWriter;

/// SFINAE whether the specified class is a property.
template <class T>
struct IsProperty;

class Property {
public:
    Property(const std::string& name);

    virtual ~Property();

    const std::string& getName() const;

    virtual bool load(const PropertyHandler& handler,
                      cocos2d::Node* node) const = 0;

    virtual bool store(PropertyHandler& handler,
                       const cocos2d::Node* node) const = 0;

private:
    std::string name_;
};

/// A node property.
template <class ValueT>
class GenericProperty : public Property {
private:
    using Super = Property;

public:
    using Value = ValueT;

    using Reader =
        std::function<std::optional<Value>(const cocos2d::Node* node)>;
    using Writer = std::function<bool(cocos2d::Node* node, const Value& value)>;

    explicit GenericProperty(const std::string& name, const Reader& reader,
                             const Writer& writer)
        : Super(name)
        , reader_(reader)
        , writer_(writer) {}

    const Reader& getReader() const { return reader_; }
    const Writer& getWriter() const { return writer_; }

    std::optional<Value> read(const cocos2d::Node* node) const {
        return getReader()(node);
    }

    bool write(cocos2d::Node* node, const Value& value) const {
        return getWriter()(node, value);
    }

    virtual bool load(const PropertyHandler& handler,
                      cocos2d::Node* node) const override;

    virtual bool store(PropertyHandler& handler,
                       const cocos2d::Node* node) const override;

private:
    Reader reader_;
    Writer writer_;
};

template <class Target, class Value>
typename GenericProperty<Value>::Reader makePropertyReader(
    const std::function<std::optional<Value>(const Target* node)>& reader) {
    return [reader](const cocos2d::Node* node_) -> std::optional<Value> {
        auto node = dynamic_cast<const Target*>(node_);
        if (node == nullptr) {
            assert(false);
            return std::nullopt;
        }
        return reader(node);
    };
}

template <class Target, class Value>
typename GenericProperty<Value>::Writer makePropertyWriter(
    const std::function<void(Target* node, const Value& value)>& writer) {
    return [writer](cocos2d::Node* node_, const Value& value) -> bool {
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
struct IsProperty<GenericProperty<T>> : std::true_type {};
} // namespace ee

#include "propertyhandler.hpp"

namespace ee {
template <class T>
bool GenericProperty<T>::load(const PropertyHandler& handler,
                              cocos2d::Node* node) const {
    return handler.loadProperty(*this, node);
}

template <class T>
bool GenericProperty<T>::store(PropertyHandler& handler,
                               const cocos2d::Node* node) const {
    return handler.storeProperty(*this, node);
}
} // namespace ee

#endif // EE_PARSER_PROPERTY_HPP
