#ifndef EE_PARSER_PROPERTY_BOOL_HPP
#define EE_PARSER_PROPERTY_BOOL_HPP

#include <string>

#include "property.hpp"

namespace ee {
class PropertyBool : public Property<bool> {
private:
    using Self = PropertyBool;
    using Super = Property;

public:
    explicit PropertyBool(const std::string& name)
        : name_(name) {}

    const std::string& name() const { return name_; }

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

#endif // EE_PARSER_PROPERTY_BOOL_HPP
