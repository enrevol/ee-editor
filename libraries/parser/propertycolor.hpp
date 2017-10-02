#ifndef EE_PARSER_PROPERTY_COLOR_HPP
#define EE_PARSER_PROPERTY_COLOR_HPP

#include <string>

#include "property.hpp"

namespace cocos2d {
struct Color3B;
} // namespace cocos2d

namespace ee {
class PropertyColor : public Property<cocos2d::Color3B> {
private:
    using Self = PropertyColor;
    using Super = Property;

public:
    explicit PropertyColor(const std::string& name)
        : name_(name) {}

    std::string nameR() const { return name_ + "_r"; }
    std::string nameG() const { return name_ + "_g"; }
    std::string nameB() const { return name_ + "_b"; }

    virtual bool addReadHandler(PropertyHandler& propertyHandler,
                                const ReadHandler& handler) const override;

    virtual bool addWriteHandler(PropertyHandler& propertyHandler,
                                 const WriteHandler& handler) const override;

    virtual Value get(const PropertyReader& reader,
                      const Value& defaultValue) const override;

    virtual void set(PropertyWriter& writer, const Value& value) const override;

    virtual bool add(PropertyWriter& writer, const Value& value) const override;

private:
    std::string name_;
};
} // namespace ee

#endif // EE_PARSER_PROPERTY_COLOR_HPP
