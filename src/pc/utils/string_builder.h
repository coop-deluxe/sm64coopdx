#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdio.h>

struct StringBuilder {
    char* string;
    int bufferLength;
};

struct StringBuilder* string_builder_create(int bufferLength);
#define string_builder_append(_builder, ...) snprintf((_builder->string + strlen(_builder->string)), (_builder->bufferLength - strlen(_builder->string)), __VA_ARGS__)
void string_builder_destroy(struct StringBuilder* builder);

#endif