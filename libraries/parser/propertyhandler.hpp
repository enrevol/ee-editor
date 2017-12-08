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

    bool hasProperty(const std::string& name) const;
    std::optional<Value> getProperty(const std::string& name) const;
    void setProperty(const std::string& name, const Value& value);

    /// Reads a property value from the specified property handler.
    /// @param name The property's name.
    template <class Value>
    std::optional<Value> getProperty(const std::string& name) const {
        return PropertyTraits<Value>::getProperty(*this, name);
    }

    /// Writes a property value to the specified property handler.
    /// @param name The property's name.
    template <class Value>
    void setProperty(const std::string& name, const Value& value) {
        PropertyTraits<Value>::setProperty(*this, name, value);
    }

    template <class Value>
    bool loadProperty(const Property<Value>& property,
                      cocos2d::Node* node) const {
        auto value = getProperty<Value>(property.getName());
        if (not value.has_value()) {
            return false;
        }
        return property.write(node, value.value());
    }

    template <class Value>
    bool storeProperty(const Property<Value>& property,
                       const cocos2d::Node* node) {
        auto value = property.read(node);
        if (not value.has_value()) {
            return false;
        }
        setProperty<Value>(property.getName(), value.value());
        return true;
    }

private:
    ValueMap properties_;
};
} // namespace ee

#endif // EE_PARSER_PROPERTY_HANDLER_HPP
