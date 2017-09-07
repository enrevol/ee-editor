#include <ciso646>

#include "contentprotectionkey.hpp"

namespace ee {
namespace key {
constexpr auto v = "content_protection_key";
} // namespace key

ContentProtectionKey::ContentProtectionKey() {}

ContentProtectionKey::ContentProtectionKey(const QString& key)
    : key_(key) {}

bool ContentProtectionKey::isEmpty() const {
    return not key_.has_value();
}

QString ContentProtectionKey::toString() const {
    return isEmpty() ? "" : key_.value();
}

bool ContentProtectionKey::deserialize(const QJsonObject& json) {
    auto&& value = json.value(key::v);
    if (value.isUndefined()) {
        // Not yet defined.
        key_.reset();
        return true;
    }
    if (value.isString()) {
        key_ = value.toString();
        return true;
    }

    // Invalid type.
    return false;
}

void ContentProtectionKey::serialize(QJsonObject& json) const {
    json.insert(key::v, toString());
}
} // namespace ee
