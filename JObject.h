#pragma once

#include <string>
#include <utility>
#include <vector>
#include <iostream>

class JObject;

enum JType {
    Object,
    Number,
    String,
    Array,
    Boolean
};

class JValue {
protected:
    JObject* _parent;
    std::string _name;
    JType _type;
    
public:
    JValue(JObject* parent, std::string name, JType type)
    : _parent(parent), _name(std::move(name)), _type(type) {}
    
    inline JObject* parent() const { return _parent; }
    inline std::string name() const { return _name; }
    inline JType type() const { return _type; }
};

class JNumber : public JValue {
protected:
    float _data;
    
public:
    JNumber(JObject* parent, std::string name, float data) : JValue(parent, std::move(name), JType::Number) {
        _data = data;
    }
    
    inline float value() const { return _data; }
    friend std::ostream& operator<<(std::ostream& os, const JNumber& num);
};

class JString : public JValue {
protected:
    std::string _data;
    
public:
    JString(JObject* parent, std::string name, std::string data) : JValue(parent, std::move(name), JType::String) {
        _data = const_cast<char*>(data.c_str());
    }
    
    inline std::string value() const { return _data; }
    friend std::ostream& operator<<(std::ostream& os, const JString& str);
};

class JBool : public JValue {
protected:
    bool _data;
    
public:
    JBool(JObject* parent, std::string name, bool data) : JValue(parent, std::move(name), JType::Boolean) {
        _data = data;
    }
    
    inline bool value() const { return _data; }
    friend std::ostream& operator<<(std::ostream& os, const JBool& boolean);
};

class JArray;

class JObject : public JValue {
protected:
//    JObject* _parent;
//    std::string _name;
//    JType _type = JType::Object;
    
    std::vector<JObject> _objects;
    std::vector<JNumber> _numbers;
    std::vector<JString> _strings;
    std::vector<JBool> _booleans;
    std::vector<JArray> _arrays;

public:
    JObject(JObject* parent, std::string name, JType type = JType::Object);
    
    inline void number(const JNumber& number) { _numbers.push_back(number); }
    inline void string(const JString& string) { _strings.push_back(string); }
    inline void boolean(const JBool& boolean) { _booleans.push_back(boolean); }
    inline void array(const JArray& arr) { _arrays.push_back(arr); }
    inline void object(const JObject& obj) { _objects.push_back(obj); }
    
    const JNumber* number(const std::string& name) const;
    const JString* string(const std::string& name) const;
    const JBool* boolean(const std::string& name) const;
    const JArray* array(const std::string& name) const;
    const JObject* object(const std::string& name) const;

    virtual int size() const;
};

class JArray : public JObject {
private:
    std::vector<JValue*> _arr;
    
public:
    JArray(JObject* parent, std::string name) 
    : JObject(parent, std::move(name), JType::Array) {}
    
    JValue* value(int index) const {
        JValue* jv = _arr.at(index);
        switch (jv->type()) {
            case JType::String: {
                return ((JString*)jv);
            }
            case JType::Number: {
                return ((JNumber*)jv);
            }
            case JType::Boolean: {
                return ((JBool*)jv);
            }
            case JType::Array: {
                return ((JArray*)jv);
            }
            case JType::Object: {
                return ((JObject*)jv);
            }
            default:
                return jv;
        }
    }
    
    inline void add(JValue* jv) { _arr.push_back(jv); }
    
    inline int size() const override { return _arr.size(); }
};

#define jarray_index(arr, cast, i) ((cast*)(arr)->value((i)))