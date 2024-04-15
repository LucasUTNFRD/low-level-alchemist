#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "helpers/vector.h"

typedef enum{
  // Single-character tokens.
   LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
  LEFT_PAREN, RIGHT_PAREN,
  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  EOF_TOKEN 
}TokenType;

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

//token functions
Token* token_create(TokenType type,char *lexeme);

#endif /* LEXER_H */

