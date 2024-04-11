#ifndef LEXER_H
#define LEXER_H
#include <stddef.h>
#include <stdbool.h>

struct Lexer {
    const char* input;
    size_t inputLength;
    size_t position;
    size_t readPosition;
    char character;
};

struct Lexer* lexer_create(const char *input);
bool isAtEnd(struct Lexer* lexer);
void _lexer_read_char(struct Lexer* lexer);

#endif /* LEXER_H */

