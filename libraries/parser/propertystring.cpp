#include "propertystring.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertywriter.hpp"

namespace ee {
using Self = PropertyString;

std::string Self::get(const PropertyReader& reader,
                      const std::string& defaultValue) const {
    return reader.getStringProperty(name(), defaultValue);
}

void Self::set(PropertyWriter& writer, const std::string& value) const {
    writer.setProperty(name(), value);
}

bool Self::add(PropertyWriter& writer, const std::string& value) const {
    return writer.addProperty(name(), value);
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    return propertyHandler.addReadStringHandler(name(), handler);
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    return propertyHandler.addWriteStringHandler(name(), handler);
}
} // namespace ee
