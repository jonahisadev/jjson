cmake_minimum_required(VERSION 3.10)
project(jjson)

set(CMAKE_CXX_STANDARD 14)

add_library(jjson SHARED json.h JsonDocument.cpp JsonDocument.h JObject.cpp JObject.h JsonLog.h)

install(TARGETS jjson DESTINATION lib)
install(FILES json.h JsonDocument.h JObject.h JsonLog.h DESTINATION include/jjson)