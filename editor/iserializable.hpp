#ifndef EE_EDITOR_I_SERIALIZABLE_HPP
#define EE_EDITOR_I_SERIALIZABLE_HPP

#include <QJsonObject>

namespace ee {
class ISerializable {
public:
    ISerializable() = default;
    virtual ~ISerializable() = default;

    /// Attempts to deserialize data from the specified json object.
    /// @param json The json object to load data from.
    virtual bool deserialize(const QJsonObject& json) = 0;

    /// Serializes this instance to a json object.
    virtual void serialize(QJsonObject& json) const = 0;
};
} // namespace ee

#endif // EE_EDITOR_I_SERIALIZABLE_HPP
