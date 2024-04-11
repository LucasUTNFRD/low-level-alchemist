#include "lexer.h"
#include <stdlib.h>
#include <string.h>



Lexer* lexer_create(const char *input){
    struct Lexer* lexer = malloc(sizeof(struct Lexer));

    lexer->input = input;
    lexer->inputLength = strlen(input);
    lexer->position = 0;
    lexer->readPosition = 0;

    _lexer_read_char(lexer);

    return lexer;
}

void lexer_clean(Lexer *lexer){
  free(lexer);
  lexer = NULL;
  //free(token_vec)
}

static bool _isAtEnd(Lexer* lexer){
    return (lexer->readPosition >= lexer->inputLength);
}

static void _lexer_read_char(struct Lexer* lexer){
    if(_isAtEnd(lexer)){
        lexer->character = '\0';
    } else {
        lexer->character = lexer->input[lexer->readPosition];
        lexer->readPosition++;
    }
}


static void _lexer_skip(Lexer* lexer){
  while (lexer->character =='\n' || lexer->character == ' '||
         lexer->character =='\r' || lexer->character == '\t') {
    _lexer_read_char(lexer);
  }
}

