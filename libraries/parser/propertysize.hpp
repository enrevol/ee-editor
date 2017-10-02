#ifndef EE_PARSER_PROPERTY_SIZE_HPP
#define EE_PARSER_PROPERTY_SIZE_HPP

#include <string>

#include "property.hpp"

namespace cocos2d {
class Size;
} // namespace cocos2d

namespace ee {
class PropertySize : public Property<cocos2d::Size> {
private:
    using Self = PropertySize;
    using Super = Property;

public:
    explicit PropertySize(const std::string& name)
        : name_(name) {}

    std::string nameX() const { return name_ + "_width"; }
    std::string nameY() const { return name_ + "_height"; }

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

#endif // EE_PARSER_PROPERTY_SIZE_HPP
