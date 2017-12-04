#ifndef EE_PARSER_PROPERTY_HANDLER_HPP
#define EE_PARSER_PROPERTY_HANDLER_HPP

#include <functional>
#include <string>

#include "property.hpp"
#include "propertytraits.hpp"
#include "value.hpp"

namespace ee {
class PropertyHandler {
private:
    using Self = PropertyHandler;

public:
    PropertyHandler();

    const ValueMap& getProperties() const;
    void setProperties(const ValueMap& properties);
    void clearProperties();

    const Value& getProperty(const std::string& name) const;
    void setProperty(const std::string& name, const Value& value);

    /// Reads a property value from the specified property handler.
    /// @param name The property's name.
    template <class Value>
    Value getProperty(const std::string& name) const {
        return PropertyTraits<Value>::getProperty(*this, name);
    }

    /// Writes a property value to the specified property handler.
    /// @param name The property's name.
    template <class Value>
    void setProperty(const std::string& name, const Value& value) {
        PropertyTraits<Value>::setProperty(*this, name, value);
    }

    template <class Target, class Value>
    void loadProperty(const Property<Target, Value>& property,
                      Target* node) const {
        auto value = getProperty<Value>(property.getName());
        property.write(node, value);
    }

    template <class Target, class Value>
    void storeProperty(const Property<Target, Value>& property,
                       const Target* node) {
        auto value = property.read(node);
        setProperty<Value>(property.getName(), value);
    }

private:
    ValueMap properties_;
};
} // namespace ee

#endif // EE_PARSER_PROPERTY_HANDLER_HPP
