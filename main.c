#include "lexer.h"
#include "helpers/vector.h"
#include <stdio.h>
#include "helpers/hashtable.h"

int main() {

    Map *keyword_dict = map_new();
    map_insert(keyword_dict,"if",IF);
    map_insert(keyword_dict,"else",ELSE);
    map_insert(keyword_dict,"or",OR);
    map_insert(keyword_dict,"class",CLASS);
    map_insert(keyword_dict,"false",IF);
    map_insert(keyword_dict,"nil",ELSE);
    map_insert(keyword_dict,"for",OR);
    map_insert(keyword_dict,"print",CLASS);
    map_insert(keyword_dict,"return",IF);
    map_insert(keyword_dict,"super",ELSE);
    map_insert(keyword_dict,"this",OR);
    map_insert(keyword_dict,"true",CLASS);
    map_insert(keyword_dict,"var",IF);
    map_insert(keyword_dict,"while",ELSE);
    map_insert(keyword_dict,"fun",ELSE);
    map_insert(keyword_dict,"and",ELSE);

  const char *input = "(==) (!=)& <";

  Lexer* lexer = lexer_create(input);

  lexer_tokenize(lexer);
  
  Vector *tokens = lexer->token_vec;
  
  //should create a vector_size function that returns how many elements are in the vecto.
  printf("%s\n",input);
  for(int i = 0; i<10;i++){
    Token *token = vector_at(tokens,i);
    printf("Token %d: Type: %d, Literal: %s\n", i, token->type, token->literal);
  }

  lexer_clean(lexer);
}
