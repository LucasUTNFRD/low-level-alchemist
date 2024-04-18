#include "lexer.h"
#include "helpers/vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



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
        //handle identifiers
        size_t len = 0;
        const char *literal = _lexer_read_identifier(lexer, &len);
        // debug output
        // if (literal) {
        //   printf("Identifier found: %.*s the lenght is also %d \n", (int)len, literal,len);
        // } else {
        //   printf("No identifier found.\n");
        // }
        //tuve que harcodear el -1 porque leia un caracter en blanco siempre
        //lo que hacia que nunca compare bien string con string.
        TokenType type= _getTokenType(literal,len-1);

        token = token_create(type, strndup(literal,len-1));
        vector_push(lexer->token_vec,token);

      }else if (isdigit(lexer->character)) {
        size_t len =0;
        const char* integer = _lexer_read_int(lexer,&len);
        const char* literal_integer = NULL;

        literal_integer = strndup(integer,len);
        token = token_create(NUMBER,literal_integer);
        vector_push(lexer->token_vec,token);
  
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

const char *_lexer_read_int(Lexer *lexer, size_t *len) {
  size_t position = lexer->position;

  while ('0' <= lexer->character && '9' >= lexer->character)  {
    _lexer_read_char(lexer);
  }

  if (len) {
    *len = lexer->position - position;
  }

  return lexer->input + position;
}


// this function loop under isalpha condition and save the length of the string readsa
const char *_lexer_read_identifier(Lexer *lexer,size_t *len){
  size_t position = lexer->position;

  while (isalpha(lexer->character)|| lexer->character =='_') {
    _lexer_skip(lexer);
    _lexer_read_char(lexer);
  }
  if (len) {
    *len = lexer->readPosition - position; //gives the size of string
  } 
  // printf("%d\n",(int)position);
  // printf("%s\n",lexer->input);
  return lexer->input + position;
}

TokenType _getTokenType(char *literal,size_t len){
    if (strncmp(literal, "fun", len) == 0) {
    return FUN;
  } else if (strncmp(literal, "and", len) == 0) {
    return AND;
  } else if (strncmp(literal, "class", len) == 0) {
    return CLASS;
  } else if (strncmp(literal, "else", len) == 0) {
    return ELSE;
  } else if (strncmp(literal, "false", len) == 0) {
    return FALSE;
  } else if (strncmp(literal, "for", len) == 0) {
    return FOR;
  } else if (strncmp(literal, "if", len) == 0) {
    return IF;
  } else if (strncmp(literal, "nil", len) == 0) {
    return NIL;
  } else if (strncmp(literal, "or", len) == 0) {
    return OR;
  } else if (strncmp(literal, "print", len) == 0) {
    return PRINT;
  } else if (strncmp(literal, "return", len) == 0) {
    return RETURN;
  } else if (strncmp(literal, "super", len) == 0) {
    return SUPER;
  } else if (strncmp(literal, "true", len) == 0) {
    return TRUE;
  } else if (strncmp(literal, "while", len) == 0) {
    return WHILE;
  } else if (strncmp(literal, "this", len) == 0) {
    return THIS;
  } else if (strncmp(literal, "var", len) == 0) {
    return VAR;
  }

  return IDENTIFIER;
}


void lexer_tokenize(Lexer* lexer){
  // int callcounter = 0;
  while(!_isAtEnd(lexer)){
    lexer_process_char(lexer);
    // callcounter++;
    // printf("call to lexer_process_char = %d \n",callcounter);
  }
}

Token* token_create(TokenType type,char *lexeme){
  Token *token = malloc(sizeof(Token));
  token->type = type;
  token->literal = lexeme;

  return token;
}

