#pragma once

#define VA_ARGS(...) , ##__VA_ARGS__
#define JSON_LOG(x, ...) { for (int i = 0; i < depth; i++) {printf("\t");} printf(x VA_ARGS(__VA_ARGS__)); }

// Change this in compilation to
// remove JSON logging
#define JSON_DEBUG

#ifndef JSON_DEBUG
#define JSON_LOG(x, ...)
#endif