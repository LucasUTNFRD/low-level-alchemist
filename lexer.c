#include "lexer.h"
#include "helpers/vector.h"
#include <stdlib.h>


Lexer* lexer_create(const char *input){
    struct Lexer* lexer = malloc(sizeof(struct Lexer));

    lexer->input = input;
    lexer->inputLength = strlen(input);
    lexer->position = 0;
    lexer->readPosition = 0;
    lexer->token_vec = vector_create(sizeof(Token));

    _lexer_read_char(lexer);

    return lexer;
}

void lexer_clean(Lexer *lexer){
  free(lexer);
  free(lexer->token_vec);
}

static bool _isAtEnd(Lexer* lexer){
    return (lexer->readPosition >= lexer->inputLength);
}

static void _lexer_read_char(struct Lexer* lexer){
    if(_isAtEnd(lexer)){
        lexer->character = '\0';
    } else {
        lexer->character = lexer->input[lexer->readPosition];
    }
    lexer->position = lexer->readPosition;
    lexer->readPosition++;
}

static char _lexer_peek_char(struct Lexer *lexer){
  if(_isAtEnd(lexer)){
    lexer->character ='\0';
  } else {
    return lexer->input[lexer->readPosition];
  }
}


static void _lexer_skip(Lexer* lexer){
  while (lexer->character =='\n' || lexer->character == ' '||
         lexer->character =='\r' || lexer->character == '\t') {
    _lexer_read_char(lexer);
  }
}

void lexer_process_char(Lexer *lexer){
  _lexer_skip(lexer);
  
  Token *token = NULL;

  switch (lexer->character) {
    case '(':
      token=token_create(TOKEN_TYPE_SYMBOL, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case ')':
      token=token_create(TOKEN_TYPE_SYMBOL, NULL); 
      vector_push(lexer->token_vec, token);
      break;
  }
  _lexer_read_char(lexer);
}

void lexer_tokenize(Lexer* lexer){
  while(!_isAtEnd(lexer)){
    lexer_process_char(lexer);
  }
}

Token* token_create(TokenType type,char *lexeme){
  Token *token = malloc(sizeof(Token));
  token->type = type;
  token->literal = lexeme;

  return token;
}


