#include "JObject.h"

#include <utility>

JObject::JObject(JObject *parent, std::string name, JType type) 
: JValue(parent, std::move(name), type)
{}

const JNumber* JObject::number(const std::string& name) const {
    for (const auto& number : _numbers) {
        if (number.name() == name)
            return &number;
    }
    return nullptr;
}

const JString *JObject::string(const std::string& name) const {
    for (const auto& string : _strings) {
        if (string.name() == name)
            return &string;
    }
    return nullptr;
}

const JBool *JObject::boolean(const std::string& name) const {
    for (const auto& boolean : _booleans) {
        if (boolean.name() == name)
            return &boolean;
    }
    return nullptr;
}

const JArray *JObject::array(const std::string& name) const {
    for (const auto& arr : _arrays) {
        if (arr.name() == name)
            return &arr;
    }
    return nullptr;
}

const JObject *JObject::object(const std::string &name) const {
    for (const auto& obj : _objects) {
        if (obj.name() == name)
            return &obj;
    }
    return nullptr;
}

int JObject::size() const {
    return _numbers.size() + _strings.size() + _booleans.size() + _arrays.size();
}

std::ostream& operator<<(std::ostream &os, const JNumber &num) {
    os << num.value();
    return os;
}

std::ostream &operator<<(std::ostream &os, const JString &str) {
    os << str.value();
    return os;
}

std::ostream &operator<<(std::ostream &os, const JBool &boolean) {
    os << (boolean.value() ? "true" : "false");
    return os;
}
