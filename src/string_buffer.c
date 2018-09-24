#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "common.h" // Required by header.h
#include "header.h" // for nospace
#include "string_buffer.h"

void string_buffer_init(struct string_buffer *buffer)
{
    size_t capacity = 100;
    char *newBuffer = malloc(capacity);
    if (newBuffer == NULL)
        nospace(__FILE__, __LINE__);
    
    buffer->capacity = capacity;
    buffer->length = 0;
    buffer->buffer = newBuffer;
}

void string_buffer_clear(struct string_buffer *buffer)
{
    buffer->length = 0;
}

void string_buffer_append_chars(struct string_buffer *buffer, char *cs, size_t count)
{
    if (buffer->capacity - buffer->length < count)
    {
        size_t incrementNeeded = count - (buffer->capacity - buffer->length);
        size_t increment = buffer->capacity;
        if (increment < incrementNeeded)
            increment = incrementNeeded;
        if (SIZE_MAX - buffer->capacity < increment)
            nospace(__FILE__, __LINE__);
        size_t newCapacity = buffer->capacity + increment;
        char *newBuffer = realloc(buffer->buffer, newCapacity);
        if (newBuffer == NULL)
            nospace(__FILE__, __LINE__);
        buffer->capacity = newCapacity;
        buffer->buffer = newBuffer;
    }

    memcpy(buffer->buffer + buffer->length, cs, count);
    buffer->length += count;
}

char *string_buffer_duplicate_string(struct string_buffer *buffer)
{
    if (buffer->length == SIZE_MAX)
        nospace(__FILE__, __LINE__);
    char *result = malloc(buffer->length + 1);
    if (result == NULL)
        nospace(__FILE__, __LINE__);
    memcpy(result, buffer->buffer, buffer->length);
    result[buffer->length] = 0;
    return result;
}

void string_buffer_destroy(struct string_buffer *buffer)
{
    buffer->length = 0;
    buffer->capacity = 0;
    free(buffer->buffer);
    buffer->buffer = 0;
}
