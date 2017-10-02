#ifndef EE_PARSER_PROPERTY_WRITER_HPP
#define EE_PARSER_PROPERTY_WRITER_HPP

#include "property.hpp"

#include <base/CCValue.h>

namespace ee {
class PropertyWriter final {
public:
    explicit PropertyWriter(cocos2d::ValueMap& properties);

    cocos2d::ValueMap& getProperties();
    const cocos2d::ValueMap& getProperties() const;

    void setProperty(const std::string& name, const cocos2d::Value& value);
    void setProperty(const std::string& name, bool value);
    void setProperty(const std::string& name, int value);
    void setProperty(const std::string& name, float value);
    void setProperty(const std::string& name, const std::string& value);

    bool addProperty(const std::string& name, const cocos2d::Value& value);
    bool addProperty(const std::string& name, bool value);
    bool addProperty(const std::string& name, int value);
    bool addProperty(const std::string& name, float value);
    bool addProperty(const std::string& name, const std::string& value);

    template <class Property, class Value = typename Property::Value,
              std::enable_if_t<IsProperty<Property>::value, int> = 0>
    void setProperty(const Property& property, const Value& value) {
        property.set(*this, value);
    }

    template <class Property, class Value = typename Property::Value,
              std::enable_if_t<IsProperty<Property>::value, int> = 0>
    bool addProperty(const Property& property, const Value& value) {
        return property.add(*this, value);
    }

private:
    cocos2d::ValueMap& properties_;
};
} // namespace ee

#endif // EE_PARSER_PROPERTY_WRITER_HPP
