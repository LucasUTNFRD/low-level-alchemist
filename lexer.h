#ifndef LEXER_H
#define LEXER_H
#include <stddef.h>
#include <stdbool.h>

typedef enum{
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_SYMBOL,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_NEWLINE

}TokenType;

typedef struct Lexer {
    const char* input;
    size_t inputLength;
    size_t position;
    size_t readPosition;
    char character;
    //type vector toke_vec
}Lexer;

typedef struct Token{
  TokenType type;
  char *literal;
}Token;

Lexer* lexer_create(const char *input);
void lexer_clean(Lexer *lexer);
static bool _isAtEnd(struct Lexer* lexer);
static void _lexer_read_char(struct Lexer* lexer);

#endif /* LEXER_H */

