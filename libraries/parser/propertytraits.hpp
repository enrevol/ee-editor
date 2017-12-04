#ifndef EE_PARSER_PROPERTY_TRAITS_HPP
#define EE_PARSER_PROPERTY_TRAITS_HPP

#include <string>

namespace ee {
class PropertyHandler;

namespace detail {
template <class Value>
class PropertyTraitsNonEnum {
public:
    /// Reads a property value from the specified property handler.
    /// @param name The property's name.
    static Value getProperty(const PropertyHandler& handler,
                             const std::string& name);

    /// Writes a property value to the specified property handler.
    /// @param name The property's name.
    static void setProperty(PropertyHandler& handler, const std::string& name,
                            const Value& value);
};

template <class Value>
class PropertyTraitsEnum {
public:
    static Value getProperty(const PropertyHandler& handler,
                             const std::string& name) {
        return static_cast<Value>(
            PropertyTraitsNonEnum<int>::getProperty(handler, name));
    }

    static void setProperty(PropertyHandler& handler, const std::string& name,
                            Value value) {
        PropertyTraitsNonEnum<int>::setProperty(handler, name,
                                                static_cast<int>(value));
    }
};
} // namespace detail

template <class Value, bool = std::is_enum<Value>::value>
class PropertyTraits;

template <class Value>
class PropertyTraits<Value, true> : public detail::PropertyTraitsEnum<Value> {};

template <class Value>
class PropertyTraits<Value, false>
    : public detail::PropertyTraitsNonEnum<Value> {};
} // namespace ee

#endif // EE_PARSER_PROPERTY_TRAITS_HPP
