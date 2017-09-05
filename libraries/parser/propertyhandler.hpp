#ifndef EE_PARSER_PROPERTY_HANDLER_HPP
#define EE_PARSER_PROPERTY_HANDLER_HPP

#include <functional>
#include <string>

#include <base/CCValue.h>

namespace ee {
class PropertyHandler {
public:
    using ReadHandler = std::function<cocos2d::Value()>;
    using ReadBoolHandler = std::function<bool()>;
    using ReadIntHandler = std::function<int()>;
    using ReadFloatHandler = std::function<float()>;
    using ReadStringHandler = std::function<std::string()>;
    using WriteHandler = std::function<bool(const cocos2d::Value& value)>;
    using WriteBoolHandler = std::function<void(bool value)>;
    using WriteIntHandler = std::function<void(int value)>;
    using WriteFloatHandler = std::function<void(float value)>;
    using WriteStringHandler = std::function<void(const std::string& value)>;

    PropertyHandler() = default;
    virtual ~PropertyHandler() = default;

    bool readBoolProperty(const std::string& name) const;
    int readIntProperty(const std::string& name) const;
    float readFloatProperty(const std::string& name) const;
    std::string readStringProperty(const std::string& name) const;

    bool writeProperty(const std::string& name,
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
