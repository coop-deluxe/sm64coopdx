#include <string.h>
#include <stdlib.h>
#include "string_builder.h"

struct StringBuilder* string_builder_create(int bufferLength) {
    struct StringBuilder* builder = malloc(sizeof(struct StringBuilder));
    builder->string = malloc(sizeof(char) * bufferLength);
    builder->string[0] = '\0';
    builder->bufferLength = bufferLength;
    return builder;
}

void string_builder_destroy(struct StringBuilder* builder) {
    free(builder->string);
    free(builder);
}
