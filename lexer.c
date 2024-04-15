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
    return (lexer->readPosition > lexer->inputLength);
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
  while (lexer->character == ' ' || lexer->character == '\t' || lexer->character == '\n' ||
         lexer->character == '\r') {
    _lexer_read_char(lexer);
  }
}
void lexer_process_char(Lexer *lexer){
  _lexer_skip(lexer);
  
  Token *token = NULL;

  switch (lexer->character) {
    case '(':
      puts("(");
      token=token_create(LEFT_PAREN, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case ')':
      puts(")");
      token=token_create(RIGHT_PAREN, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case '{':
      puts("{");
      token=token_create(RIGHT_BRACE, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case '}':
      puts("}");
      token=token_create(RIGHT_BRACE, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case '+':
      puts("+");
      token=token_create(PLUS, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case '-':
      puts("-");
      token=token_create(MINUS, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case '.':
      puts(".");
      token=token_create(DOT, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case ',':
      puts(",");
      token=token_create(COMMA, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case ';':
      puts(";");
      token=token_create(SEMICOLON, NULL); 
      vector_push(lexer->token_vec, token);
      break;
    case '*':
      puts("*");
      token=token_create(STAR, NULL); 
      vector_push(lexer->token_vec, token);
      break;
  }
  _lexer_read_char(lexer);
}

void lexer_tokenize(Lexer* lexer){
  int callcounter = 0;
  while(!_isAtEnd(lexer)){
    lexer_process_char(lexer);
    callcounter++;
    printf("call to lexer_process_char = %d \n",callcounter);
  }
}

Token* token_create(TokenType type,char *lexeme){
  Token *token = malloc(sizeof(Token));
  token->type = type;
  token->literal = lexeme;

  return token;
}


