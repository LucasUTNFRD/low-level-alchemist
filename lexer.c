#include "lexer.h"
#include "helpers/vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    case '=':
      if(_lexer_peek_char(lexer) == '='){
        _lexer_read_char(lexer);
        token=token_create(EQUAL_EQUAL, NULL);
        vector_push(lexer->token_vec, token);
        puts("==");
      } else {
        puts("=");
        token=token_create(EQUAL_EQUAL,NULL);
        vector_push(lexer->token_vec, token);
      }
      break;
    case '!':
      if (_lexer_peek_char(lexer)=='=') {
        _lexer_read_char(lexer);
        token=token_create(BANG_EQUAL,NULL) ;
        vector_push(lexer->token_vec, token);
        puts("!=");
      }else {
        token=token_create(BANG,NULL);
        vector_push(lexer->token_vec, NULL);
        puts("!");
      }
      break;
    case '<':
      if (_lexer_peek_char(lexer)=='=') {
        _lexer_read_char(lexer);
        token=token_create(LESS_EQUAL,NULL) ;
        vector_push(lexer->token_vec, token);
        puts("<=");
      }else {
        token=token_create(LESS,NULL);
        vector_push(lexer->token_vec, token);
        puts("<");
      }
      break;
    case '>':
      if (_lexer_peek_char(lexer)=='=') {
        _lexer_read_char(lexer);
        token=token_create(GREATER_EQUAL,NULL) ;
        vector_push(lexer->token_vec, token);
        puts(">=");
      }else {
        token=token_create(GREATER,NULL);
        vector_push(lexer->token_vec, token);
        puts(">");
      }
      break;
    case '\0':
      token=token_create(EOF_TOKEN, NULL);
      vector_push(lexer->token_vec,token);
      puts("EOF");
      break;
    case '/':
      //handle comments
      token=token_create(SLASH, NULL);
      vector_push(lexer->token_vec,token);
      break;
    case '"':
      break;
    default:
      if(isalpha(lexer->character) || lexer->character == '_'){

      }else if (isdigit(lexer->character)) {
  
      }else {
        fprintf(stderr, "Error: character '%c' is not alphanumeric",lexer->character);
        exit(EXIT_FAILURE);
      }
  }
  //handle identifiers
  //handle numbers
  //handle string literals


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

