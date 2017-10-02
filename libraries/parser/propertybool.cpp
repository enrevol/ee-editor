#include "propertybool.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertywriter.hpp"

namespace ee {
using Self = PropertyBool;

bool Self::get(const PropertyReader& reader, const bool& defaultValue) const {
    return reader.getBoolProperty(name(), defaultValue);
}

void Self::set(PropertyWriter& writer, const bool& value) const {
    writer.setProperty(name(), value);
}

bool Self::add(PropertyWriter& writer, const bool& value) const {
    return writer.addProperty(name(), value);
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    return propertyHandler.addReadBoolHandler(name(), handler);
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    return propertyHandler.addWriteBoolHandler(name(), handler);
}
} // namespace ee
