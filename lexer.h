#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "helpers/vector.h"
#include "helpers/types.h"


typedef struct Token{
  TokenType type;
  char *literal;
}Token;

typedef struct Lexer {
  
    const char* input;
    size_t inputLength;
    size_t position;
    size_t readPosition;
    char character;
    //type vector toke_vec
    Vector *token_vec;

}Lexer;

//lexer functions

Lexer* lexer_create(const char *input);
void lexer_clean(Lexer *lexer);
static bool _isAtEnd(struct Lexer* lexer);
static void _lexer_read_char(struct Lexer* lexer);
static char _lexer_peek_char(struct Lexer* lexer);
void lexer_tokenize(Lexer *lexer);
void lexer_process_char(Lexer* lexer);
static const char *_lexer_read_identifier(Lexer *lexer,size_t *len);
//token functions
Token* token_create(TokenType type,char *lexeme);

#endif /* LEXER_H */

