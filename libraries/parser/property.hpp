#ifndef EE_PARSER_PROPERTY_HPP
#define EE_PARSER_PROPERTY_HPP

#include <functional>

namespace cocos2d {
class Node;
} // namespace cocos2d

namespace ee {
class PropertyHandler;
class PropertyReader;
class PropertyWriter;

namespace detail {
class PropertyBase {};
} // namespace detail

template <class T> class Property : detail::PropertyBase {
public:
    using Value = T;
    using ReadHandler = std::function<Value(const cocos2d::Node* node)>;
    using WriteHandler =
        std::function<bool(cocos2d::Node* node, const Value& value)>;

    virtual ~Property() = default;

    virtual bool addReadHandler(PropertyHandler& propertyHandler,
                                const ReadHandler& handler) const = 0;

    virtual bool addWriteHandler(PropertyHandler& propertyHandler,
                                 const WriteHandler& handler) const = 0;

    virtual Value get(const PropertyReader& reader,
                      const Value& defaultValue) const = 0;

    virtual void set(PropertyWriter& writer, const Value& value) const = 0;

    virtual bool add(PropertyWriter& writer, const Value& value) const = 0;
};

template <class T>
struct IsProperty : std::is_base_of<detail::PropertyBase, T> {};
} // namespace ee

#endif // EE_PARSER_PROPERTY_HPP
