#ifndef EE_EDITOR_CONTENT_PROTECTION_KEY_HPP
#define EE_EDITOR_CONTENT_PROTECTION_KEY_HPP

#include "iserializable.hpp"
#include "optional.hpp"

#include <QString>

namespace ee {
class ContentProtectionKey : public ISerializable {
public:
    /// Constructs an empty key.
    ContentProtectionKey();

    /// Constructs a key with the specified string.
    /// @param key The key.
    ContentProtectionKey(const QString& key);

    bool isEmpty() const;

    QString toString() const;

    virtual bool deserialize(const QJsonObject& object) override;
    virtual void serialize(QJsonObject& json) const override;

private:
    std::optional<QString> key_;
};
} // namespace ee

#endif // EE_EDITOR_CONTENT_PROTECTION_KEY_HPP
