#include "lexer.h"
#include <stdlib.h>
#include <string.h>

struct Lexer* lexer_create(const char *input){
    struct Lexer* lexer = malloc(sizeof(struct Lexer));

    lexer->input = input;
    lexer->inputLength = strlen(input);
    lexer->position = 0;
    lexer->readPosition = 0;

    _lexer_read_char(lexer);

    return lexer;
}

bool isAtEnd(struct Lexer* lexer){
    return (lexer->readPosition >= lexer->inputLength);
}

void _lexer_read_char(struct Lexer* lexer){
    if(isAtEnd(lexer)){
        lexer->character = '\0';
    } else {
        lexer->character = lexer->input[lexer->readPosition];
        lexer->readPosition++;
    }
}

