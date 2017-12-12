#ifndef EE_PARSER_PROPERTY_HANDLER_HPP
#define EE_PARSER_PROPERTY_HANDLER_HPP

#include <functional>
#include <string>

#include "parserfwd.hpp"
#include "propertytraits.hpp"

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
    template <class T>
    std::optional<T> getProperty(const std::string& name) const {
        return PropertyTraits<T>::getProperty(*this, name);
    }

    /// Writes a property value to the specified property handler.
    /// @param name The property's name.
    template <class T>
    void setProperty(const std::string& name, const T& value) {
        PropertyTraits<T>::setProperty(*this, name, value);
    }

    bool loadProperty(const Property& property, cocos2d::Node* node) const;
    bool storeProperty(const Property& property, const cocos2d::Node* node);

    template <class T>
    bool loadProperty(const GenericProperty<T>& property,
                      cocos2d::Node* node) const;

    template <class T>
    bool storeProperty(const GenericProperty<T>& property,
                       const cocos2d::Node* node);

private:
    ValueMap properties_;
};
} // namespace ee

#include "property.hpp"

namespace ee {
template <class T>
bool PropertyHandler::loadProperty(const GenericProperty<T>& property,
                                   cocos2d::Node* node) const {
    auto value = getProperty<T>(property.getName());
    if (not value.has_value()) {
        return false;
    }
    return property.write(node, value.value());
}

template <class T>
bool PropertyHandler::storeProperty(const GenericProperty<T>& property,
                                    const cocos2d::Node* node) {
    auto value = property.read(node);
    if (not value.has_value()) {
        return false;
    }
    setProperty<T>(property.getName(), value.value());
    return true;
}
} // namespace ee

#endif // EE_PARSER_PROPERTY_HANDLER_HPP
