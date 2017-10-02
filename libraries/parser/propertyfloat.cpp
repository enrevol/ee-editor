#include "propertyfloat.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertywriter.hpp"

namespace ee {
using Self = PropertyFloat;

float Self::get(const PropertyReader& reader, const Value& defaultValue) const {
    return reader.getFloatProperty(name(), defaultValue);
}

void Self::set(PropertyWriter& writer, const Value& value) const {
    writer.setProperty(name(), value);
}

bool Self::add(PropertyWriter& writer, const Value& value) const {
    return writer.addProperty(name(), value);
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    return propertyHandler.addReadFloatHandler(name(), handler);
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    return propertyHandler.addWriteFloatHandler(name(), handler);
}
} // namespace ee
