#ifndef STRING_BUFFER_INCLUDED
#define STRING_BUFFER_INCLUDED

struct string_buffer {
    size_t capacity;
    size_t length;
    char *buffer;
};

void string_buffer_init(struct string_buffer *buffer);
void string_buffer_clear(struct string_buffer *buffer);
void string_buffer_append_chars(struct string_buffer *buffer, char *cs, size_t count);
char *string_buffer_duplicate_string(struct string_buffer *buffer);
void string_buffer_destroy(struct string_buffer *buffer);

#endif
