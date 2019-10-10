#include "JsonDocument.h"

JObject* JSONDocument::parseFromFile(const std::string &path) {
    FILE* file = fopen(path.c_str(), "r");
    if (!file) {
        std::cerr << "Could not open file '" << path << "'" << std::endl;
        throw;
    }

    fseek(file, 0, SEEK_END);
    int size = int(ftell(file));
    fseek(file, 0, SEEK_SET);

    char* buffer = new char[size + 1];
    fread(buffer, 1, size, file);
    fclose(file);
    buffer[size] = '\0';

    JObject* root = parse(buffer);
    delete[] buffer;
    
    return root;
}

JObject* JSONDocument::parse(const std::string& src) {
    const char* buffer = src.c_str();

    JObject* current_obj = nullptr;
    std::string current_str;
    
    char lex[256];
    int lexi = 0;
    int index = 0;
    int depth = 0;
    bool in_string = false;
    
    while (buffer[index] != '\0') {
        
        while (!is_special(buffer[index])) {
            if (buffer[index] == '"') { in_string = !in_string; }
            if (is_ws(buffer[index]) && !in_string) { index++; continue; }
            lex[lexi++] = buffer[index++];
        }

        if (buffer[index] == '\0') break;
        
        if (lexi == 0)  {
            switch (buffer[index]) {
                case '{': {
                    JSON_LOG("New object (name: %s)\n", current_str.c_str());
                    current_obj = new JObject(current_obj, current_str);
                    current_str.clear();
                    depth++;
                    break;
                }
                case '}': {
                    depth--;
                    JSON_LOG("End of object\n");
                    if (current_obj->parent()) {
                        if (current_obj->parent()->type() == JType::Array) {
                            JSON_LOG("Adding object to array\n");
                            ((JArray*)current_obj->parent())->add(current_obj);
                        }
                        JObject* temp = current_obj;
                        current_obj = current_obj->parent();
                        current_obj->object(*temp);
                    }
                    break;
                }
                case '[': {
                    JSON_LOG("New array (name: %s)\n", current_str.c_str());
                    current_obj = new JArray(current_obj, current_str);
                    current_str.clear();
                    depth++;
                    break;
                }
                case ']': {
                    depth--;
                    JSON_LOG("End of array\n");
                    if (current_obj->parent()) {
                        if (current_obj->parent()->type() == JType::Array) {
                            JSON_LOG("Adding array to array\n");
                            ((JArray*)current_obj->parent())->add(current_obj);
                        }
                        JArray* temp = (JArray*)current_obj;
                        current_obj = current_obj->parent();
                        current_obj->array(*temp);
                    }
                    break;
                }
            }
            
            index++;
            lexi = 0;
            continue;
        }
        
        lex[lexi] = '\0';
        
        // String
        if (lex[0] == '"' && lex[strlen(lex) - 1] == '"') {
            JSON_LOG("String: %s\n", lex);
            if (current_obj->type() == JType::Object) {
                if (current_str.empty()) {
                    current_str = std::string(lex);
                    current_str = current_str.substr(1, current_str.length() - 2); // Trim quotes
                } else {
                    JSON_LOG("Key/value: %s, %s\n", current_str.c_str(), lex);
                    std::string name = std::string(lex);
                    name = name.substr(1, name.length() - 2); // Trim quotes
                    current_obj->string({current_obj, current_str, name});
                    current_str.clear();
                }
            }
            else if (current_obj->type() == JType::Array) {
                JSON_LOG("String in array: %s\n", lex);
                std::string val = std::string(lex);
                val = val.substr(1, val.length() - 2); // Trim quotes
                auto str = new JString(current_obj, "", val);
                ((JArray*)current_obj)->add(str);
            }
        }
        
        // Number
        if (is_num(lex)) {
            JSON_LOG("Number: %s\n", lex);
            if (current_obj->type() == JType::Object) {
                if (!current_str.empty()) {
                    JSON_LOG("Key/value: %s, %s\n", current_str.c_str(), lex);
                    int num = std::stoi(lex);
                    current_obj->number({current_obj, current_str, (float) num});
                    current_str.clear();
                } else {
                    // ERROR
                    std::cerr << "JSON Syntax error" << std::endl;
                }
            } else if (current_obj->type() == JType::Array) {
                JSON_LOG("Number in array: %s\n", lex);
                int num = std::stoi(lex);
                auto jn = new JNumber(current_obj, "", num);
                ((JArray*)current_obj)->add(jn);
            }
        }
        
        // Boolean
        if (!strcmp(lex, "true") || !strcmp(lex, "false")) {
            JSON_LOG("Boolean: %s\n", lex);
            if (current_obj->type() == JType::Object) {
                if (!current_str.empty()) {
                    JSON_LOG("Key/value: %s, %s\n", current_str.c_str(), lex);
                    bool boolean = !strcmp(lex, "true");
                    current_obj->boolean({current_obj, current_str, boolean});
                    current_str.clear();
                } else {
                    // ERROR
                    std::cerr << "JSON syntax error" << std::endl;
                }
            } else if (current_obj->type() == JType::Array) {
                JSON_LOG("Boolean in array: %s\n", lex);
                bool boolean = !strcmp(lex, "true");
                auto jb = new JBool(current_obj, "", boolean);
                ((JArray*)current_obj)->add(jb);
            }
        }
        
        lexi = 0;
//        index++;
    }
    
    return current_obj;
}

bool JSONDocument::is_special(char c) {
    return (c == '{' || c == ':' || c == ',' || c == '}' || c == '[' || c == ']' || c == '\0');
}

bool JSONDocument::is_ws(char c) {
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
}

bool JSONDocument::is_num(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] > '9' || str[i] < '0')
            return false;
    }
    return true;
}
