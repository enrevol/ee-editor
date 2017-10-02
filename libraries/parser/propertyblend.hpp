#ifndef EE_PARSER_PROPERTY_BLEND_HPP
#define EE_PARSER_PROPERTY_BLEND_HPP

#include <string>

#include "property.hpp"

namespace cocos2d {
struct BlendFunc;
} // namespace cocos2d

namespace ee {
class PropertyBlend : public Property<cocos2d::BlendFunc> {
private:
    using Self = PropertyBlend;
    using Super = Property;

public:
    explicit PropertyBlend(const std::string& name)
        : name_(name) {}

    std::string nameSrc() const { return name_ + "_src"; }
    std::string nameDst() const { return name_ + "_dst"; }

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

#endif // EE_PARSER_PROPERTY_BLEND_HPP
