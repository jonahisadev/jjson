#include <iostream>

#define JSON_DEBUG
#include "../json.h"

int main(int argc, char** argv) {
    JObject* root = JSONDocument::parseFromFile("file.json");

    std::cout << "Name: " << *root->string("name") << std::endl;
    std::cout << "Age: " << *root->number("age") << std::endl;

    std::cout << "Classes:" << std::endl;
    const JArray* cls = root->array("classes");
    for (int i = 0; i < cls->size(); i++) {
        auto str = jarray_index(cls, JString, i);
        std::cout << *str << std::endl;
    }

    std::cout << "Dog:" << std::endl;
    const JObject* dog = root->object("dog");
    std::cout << *dog->string("name") << std::endl;
    std::cout << *dog->number("age") << std::endl;

    delete root;
    return 0;
}