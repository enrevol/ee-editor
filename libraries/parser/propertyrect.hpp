#ifndef EE_PARSER_PROPERTY_RECT_HPP
#define EE_PARSER_PROPERTY_RECT_HPP

#include <string>

#include "property.hpp"

namespace cocos2d {
class Rect;
} // namespace cocos2d

namespace ee {
class PropertyRect : public Property<cocos2d::Rect> {
private:
    using Self = PropertyRect;
    using Super = Property;

public:
    explicit PropertyRect(const std::string& name)
        : name_(name) {}

    std::string nameX() const { return name_ + "_x"; }
    std::string nameY() const { return name_ + "_y"; }
    std::string nameW() const { return name_ + "_width"; }
    std::string nameH() const { return name_ + "_height"; }

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

#endif // EE_PARSER_PROPERTY_RECT_HPP
