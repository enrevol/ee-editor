#ifndef EE_PARSER_PROPERTY_HANDLER_HPP
#define EE_PARSER_PROPERTY_HANDLER_HPP

#include <functional>
#include <string>

#include <base/CCValue.h>

namespace ee {
class PropertyHandler {
public:
    using ReadHandler =
        std::function<cocos2d::Value(const cocos2d::Node* node)>;

    using ReadBoolHandler = std::function<bool(const cocos2d::Node* node)>;

    using ReadIntHandler = std::function<int(const cocos2d::Node* node)>;

    using ReadFloatHandler = std::function<float(const cocos2d::Node* node)>;

    using ReadStringHandler =
        std::function<std::string(const cocos2d::Node* node)>;

    using WriteHandler =
        std::function<bool(cocos2d::Node* node, const cocos2d::Value& value)>;

    using WriteBoolHandler =
        std::function<void(cocos2d::Node* node, bool value)>;

    using WriteIntHandler = std::function<void(cocos2d::Node* node, int value)>;

    using WriteFloatHandler =
        std::function<void(cocos2d::Node* node, float value)>;

    using WriteStringHandler =
        std::function<void(cocos2d::Node* node, const std::string& value)>;

    PropertyHandler() = default;
    virtual ~PropertyHandler() = default;

    /// Reads a bool property.
    /// @param name The name of the property
    /// @param defaultValue The default value if the property doesn't exist.
    /// @return The property value.
    bool readBoolProperty(const cocos2d::Node* node, const std::string& name,
                          bool defaultValue = false) const;

    /// Reads an int property.
    /// @param name The name of the property
    /// @param defaultValue The default value if the property doesn't exist.
    /// @return The property value.
    int readIntProperty(const cocos2d::Node* node, const std::string& name,
                        int defaultValue = 0) const;

    /// Reads a float property.
    /// @param name The name of the property
    /// @param defaultValue The default value if the property doesn't exist.
    /// @return The property value.
    float readFloatProperty(const cocos2d::Node* node, const std::string& name,
                            float defaultValue = 0.0f) const;

    /// Reads a string property.
    /// @param name The name of the property
    /// @param defaultValue The default value if the property doesn't exist.
    /// @return The property value.
    std::string
    readStringProperty(const cocos2d::Node* node, const std::string& name,
                       std::string defaultValue = std::string()) const;

    /// Attempts to write a property.
    /// @param name The name of the property.
    /// @param value The value to write.
    /// @return True if the property was written, false otherwise.
    bool writeProperty(cocos2d::Node* node, const std::string& name,
                       const cocos2d::Value& value) const;

    bool addReadHandler(const std::string& name, const ReadHandler& handler);

    bool addReadBoolHandler(const std::string name,
                            const ReadBoolHandler& handler);

    bool addReadIntHandler(const std::string name,
                           const ReadIntHandler& handler);

    bool addReadFloatHandler(const std::string name,
                             const ReadFloatHandler& handler);

    bool addReadStringHandler(const std::string name,
                              const ReadStringHandler& handler);

    bool addWriteHandler(const std::string& name, const WriteHandler& handler);

    bool addWriteBoolHandler(const std::string& name,
                             const WriteBoolHandler& handler);

    bool addWriteIntHandler(const std::string& name,
                            const WriteIntHandler& handler);

    bool addWriteFloatHandler(const std::string& name,
                              const WriteFloatHandler& handler);

    bool addWriteStringHandler(const std::string& name,
                               const WriteStringHandler& handler);

private:
    std::unordered_map<std::string, ReadHandler> readHandlers_;
    std::unordered_map<std::string, WriteHandler> writeHandlers_;
};
} // namespace ee

#endif // EE_PARSER_PROPERTY_HANDLER_HPP
