#pragma once

#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "JsonLog.h"
#include "JObject.h"

class JSONDocument {
private:
    static bool is_special(char c);
    static bool is_ws(char c);
    static bool is_num(char* str);
    
public:
    static JObject* parseFromFile(const std::string& path);
    static JObject* parse(const std::string& src);
};