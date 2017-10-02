#include "propertyint.hpp"
#include "propertyhandler.hpp"
#include "propertyreader.hpp"
#include "propertywriter.hpp"

namespace ee {
using Self = PropertyInt;

int Self::get(const PropertyReader& reader, const int& defaultValue) const {
    return reader.getIntProperty(name(), defaultValue);
}

void Self::set(PropertyWriter& writer, const int& value) const {
    writer.setProperty(name(), value);
}

bool Self::add(PropertyWriter& writer, const int& value) const {
    return writer.addProperty(name(), value);
}

bool Self::addReadHandler(PropertyHandler& propertyHandler,
                          const ReadHandler& handler) const {
    return propertyHandler.addReadIntHandler(name(), handler);
}

bool Self::addWriteHandler(PropertyHandler& propertyHandler,
                           const WriteHandler& handler) const {
    return propertyHandler.addWriteIntHandler(name(), handler);
}
} // namespace ee
