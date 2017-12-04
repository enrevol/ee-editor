#ifndef EE_PARSER_VALUE_HPP
#define EE_PARSER_VALUE_HPP

#include <map>
#include <string>
#include <vector>

namespace ee {
class Value;

using ValueList = std::vector<Value>;
using ValueMap = std::map<std::string, Value>;

class Value final {
private:
    using Self = Value;

public:
    enum class Type {
        None,   ///< Empty.
        Bool,   ///< Wraps a bool.
        Int,    ///< Wraps an integer.
        Float,  ///< Wraps a float.
        String, ///< Wraps a string.
        List,   ///< Wraps a list of values.
        Map     ///< Wraps a map of values.
    };

    static const Self Null;

    Value();

    explicit Value(bool value);
    explicit Value(int value);
    explicit Value(float value);
    explicit Value(const std::string& value);
    explicit Value(std::string&& value);
    explicit Value(const ValueList& value);
    explicit Value(ValueList&& value);
    explicit Value(const ValueMap& value);
    explicit Value(ValueMap&& value);

    Value(const Self& other);
    Value(Self&& other);

    ~Value();

    Self& operator=(const Self& other);
    Self& operator=(Self&& other);

    Self& operator=(bool value);
    Self& operator=(int value);
    Self& operator=(float value);
    Self& operator=(const std::string& value);
    Self& operator=(std::string&& value);
    Self& operator=(const ValueList& value);
    Self& operator=(ValueList&& value);
    Self& operator=(const ValueMap& value);
    Self& operator=(ValueMap&& value);

    bool operator==(const Self& other) const;
    bool operator!=(const Self& other) const;

    bool getBool() const;
    int getInt() const;
    float getFloat() const;
    const std::string& getString() const;
    ValueList& getList();
    const ValueList& getList() const;
    ValueMap& getMap();
    const ValueMap& getMap() const;

    bool isNull() const;

    Type getType() const;

    void clear();

private:
    Self& operator=(const std::unique_ptr<std::string>& value);
    Self& operator=(std::unique_ptr<std::string>&& value);
    Self& operator=(const std::unique_ptr<ValueList>& value);
    Self& operator=(std::unique_ptr<ValueList>&& value);
    Self& operator=(const std::unique_ptr<ValueMap>& value);
    Self& operator=(std::unique_ptr<ValueMap>&& value);

    Type type_;

    union Field {
        bool b;
        int i;
        float f;
        std::unique_ptr<std::string> s;
        std::unique_ptr<ValueList> l;
        std::unique_ptr<ValueMap> m;

        Field() {}
        ~Field() {}
    } field_;
};
} // namespace ee

#endif // VALUE_HPP
