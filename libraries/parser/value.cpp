#include <cassert>
#include <cmath>
#include <numeric>

#include "value.hpp"

#include <base/CCValue.h>

namespace ee {
using Self = Value;

const Self Self::Null = Self();

Self Self::fromValue(const cocos2d::Value& value) {
    switch (value.getType()) {
    case cocos2d::Value::Type::BOOLEAN:
        return Self(value.asBool());
    case cocos2d::Value::Type::INTEGER:
        return Self(value.asInt());
    case cocos2d::Value::Type::FLOAT:
        return Self(value.asFloat());
    case cocos2d::Value::Type::STRING:
        return Self(value.asString());
    case cocos2d::Value::Type::VECTOR: {
        ValueList array;
        for (auto&& elt : value.asValueVector()) {
            array.emplace_back(fromValue(elt));
        }
        return Self(array);
    }
    case cocos2d::Value::Type::MAP: {
        ValueMap dict;
        for (auto&& elt : value.asValueMap()) {
            dict.emplace(elt.first, fromValue(elt.second));
        }
        return Self(dict);
    }
    default:
        return Null;
    }
}

cocos2d::Value Self::toValue() const {
    switch (getType()) {
    case Type::Bool:
        return cocos2d::Value(getBool().value());
    case Type::Int:
        return cocos2d::Value(getInt().value());
    case Type::Float:
        return cocos2d::Value(getFloat().value());
    case Type::String:
        return cocos2d::Value(asString());
    case Type::List: {
        cocos2d::ValueVector array;
        for (auto&& elt : asList()) {
            array.emplace_back(elt.toValue());
        }
        return cocos2d::Value(std::move(array));
    }
    case Type::Map: {
        cocos2d::ValueMap dict;
        for (auto&& elt : asMap()) {
            dict.emplace(elt.first, elt.second.toValue());
        }
        return cocos2d::Value(std::move(dict));
    }
    default:
        return cocos2d::Value::Null;
    }
}

Self::Value() {
    type_ = Type::None;
}

Self::Value(bool value) {
    type_ = Type::None;
    *this = value;
}

Self::Value(int value) {
    type_ = Type::None;
    *this = value;
}

Self::Value(float value) {
    type_ = Type::None;
    *this = value;
}

Self::Value(const std::string& value) {
    type_ = Type::None;
    *this = value;
}

Self::Value(std::string&& value) {
    type_ = Type::None;
    *this = std::move(value);
}

Self::Value(const ValueList& value) {
    type_ = Type::None;
    *this = value;
}

Self::Value(ValueList&& value) {
    type_ = Type::None;
    *this = std::move(value);
}

Self::Value(const ValueMap& value) {
    type_ = Type::None;
    *this = value;
}

Self::Value(ValueMap&& value) {
    type_ = Type::None;
    *this = std::move(value);
}

Self::Value(const Self& other) {
    type_ = Type::None;
    *this = other;
}

Self::Value(Self&& other) {
    type_ = Type::None;
    *this = std::move(other);
}

Self::~Value() {
    clear();
}

Self& Self::operator=(const Self& other) {
    if (this == &other) {
        return *this;
    }
    switch (other.type_) {
    case Type::None:
        clear();
        break;
    case Type::Bool:
        *this = other.field_.b;
        break;
    case Type::Int:
        *this = other.field_.i;
        break;
    case Type::Float:
        *this = other.field_.f;
        break;
    case Type::String:
        *this = other.field_.s;
        break;
    case Type::List:
        *this = other.field_.l;
        break;
    case Type::Map:
        *this = other.field_.m;
        break;
    }
    return *this;
}

Self& Self::operator=(Self&& other) {
    if (this == &other) {
        return *this;
    }
    switch (other.type_) {
    case Type::None:
        clear();
        break;
    case Type::Bool:
        *this = std::move(other.field_.b);
        break;
    case Type::Int:
        *this = std::move(other.field_.i);
        break;
    case Type::Float:
        *this = std::move(other.field_.f);
        break;
    case Type::String:
        *this = std::move(other.field_.s);
        break;
    case Type::List:
        *this = std::move(other.field_.l);
        break;
    case Type::Map:
        *this = std::move(other.field_.m);
        break;
    }
    type_ = other.type_;
    other.clear();
    return *this;
}

Self& Self::operator=(bool value) {
    clear();
    field_.b = value;
    type_ = Type::Bool;
    return *this;
}

Self& Self::operator=(int value) {
    clear();
    field_.i = value;
    type_ = Type::Int;
    return *this;
}
Self& Self::operator=(float value) {
    clear();
    field_.f = value;
    type_ = Type::Float;
    return *this;
}

Self& Self::operator=(const std::string& value) {
    return *this = std::make_unique<std::string>(value);
}

Self& Self::operator=(std::string&& value) {
    return *this = std::make_unique<std::string>(std::move(value));
}

Self& Self::operator=(const ValueList& value) {
    return *this = std::make_unique<ValueList>(value);
}

Self& Self::operator=(ValueList&& value) {
    return *this = std::make_unique<ValueList>(std::move(value));
}

Self& Self::operator=(const ValueMap& value) {
    return *this = std::make_unique<ValueMap>(value);
}

Self& Self::operator=(ValueMap&& value) {
    return *this = std::make_unique<ValueMap>(std::move(value));
}

Self& Self::operator=(const std::unique_ptr<std::string>& value) {
    clear();
    new (&field_.s) std::unique_ptr<std::string>(new std::string(*value));
    type_ = Type::String;
    return *this;
}

Self& Self::operator=(std::unique_ptr<std::string>&& value) {
    clear();
    new (&field_.s) std::unique_ptr<std::string>(std::move(value));
    type_ = Type::String;
    return *this;
}

Self& Self::operator=(const std::unique_ptr<ValueList>& value) {
    clear();
    new (&field_.l) std::unique_ptr<ValueList>(new ValueList(*value));
    type_ = Type::List;
    return *this;
}

Self& Self::operator=(std::unique_ptr<ValueList>&& value) {
    clear();
    new (&field_.l) std::unique_ptr<ValueList>(std::move(value));
    type_ = Type::List;
    return *this;
}

Self& Self::operator=(const std::unique_ptr<ValueMap>& value) {
    clear();
    new (&field_.m) std::unique_ptr<ValueMap>(new ValueMap(*value));
    type_ = Type::Map;
    return *this;
}

Self& Self::operator=(std::unique_ptr<ValueMap>&& value) {
    clear();
    new (&field_.m) std::unique_ptr<ValueMap>(std::move(value));
    type_ = Type::Map;
    return *this;
}

bool Self::operator==(const Self& other) const {
    if (this == &other) {
        return true;
    }
    if (getType() != other.getType()) {
        return false;
    }
    switch (getType()) {
    case Type::None:
        return true;
    case Type::Bool:
        return getBool() == other.getBool();
    case Type::Int:
        return getInt() == other.getInt();
    case Type::Float:
        return std::abs(getFloat().value() - other.getFloat().value()) <=
               std::numeric_limits<float>::epsilon();
    case Type::String:
        return asString() == other.asString();
    case Type::List:
        return asList() == other.asList();
    case Type::Map:
        return asMap() == other.asMap();
    }
    assert(false);
}

bool Self::operator!=(const Self& other) const {
    return !(*this == other);
}

Self::Type Self::getType() const {
    return type_;
}

bool Self::isNull() const {
    return getType() == Type::None;
}

bool Self::isBool() const {
    return getType() == Type::Bool;
}

bool Self::isInt() const {
    return getType() == Type::Int;
}

bool Self::isFloat() const {
    return getType() == Type::Float;
}

bool Self::isString() const {
    return getType() == Type::String;
}

bool Self::isList() const {
    return getType() == Type::List;
}

bool Self::isMap() const {
    return getType() == Type::Map;
}

std::optional<bool> Self::getBool() const {
    return isBool() ? std::make_optional(field_.b) : std::nullopt;
}

std::optional<int> Self::getInt() const {
    return isInt() ? std::make_optional(field_.i) : std::nullopt;
}

std::optional<float> Self::getFloat() const {
    return isFloat() ? std::make_optional(field_.f)
                     : map(getInt(), [](int value) {
                           // Qt Json may store float as int.
                           return std::make_optional<float>(value);
                       });
}

std::optional<std::string> Self::getString() const {
    return isString() ? std::make_optional(*field_.s) : std::nullopt;
}

std::optional<ValueList> Self::getList() const {
    return isList() ? std::make_optional(*field_.l) : std::nullopt;
}

std::optional<ValueMap> Self::getMap() const {
    return isMap() ? std::make_optional(*field_.m) : std::nullopt;
}

const std::string& Self::asString() const {
    assert(isString());
    return *field_.s;
}

ValueList& Self::asList() {
    assert(isList());
    return *field_.l;
}

const ValueList& Self::asList() const {
    assert(isList());
    return *field_.l;
}

ValueMap& Self::asMap() {
    assert(isMap());
    return *field_.m;
}

const ValueMap& Self::asMap() const {
    assert(isMap());
    return *field_.m;
}

void Self::clear() {
    switch (getType()) {
    case Type::None:
        break;
    case Type::Bool:
        field_.b = false;
        break;
    case Type::Int:
        field_.i = 0;
        break;
    case Type::Float:
        field_.f = 0;
        break;
    case Type::String:
        field_.s.~unique_ptr();
        break;
    case Type::List:
        field_.l.~unique_ptr();
        break;
    case Type::Map:
        field_.m.~unique_ptr();
        break;
    }
    type_ = Type::None;
}
} // namespace ee
