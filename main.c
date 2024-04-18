#include "lexer.h"
#include "helpers/vector.h"
#include <stdio.h>

int main() {

  const char *input = "z < 15";

  Lexer* lexer = lexer_create(input);

  lexer_tokenize(lexer);
  
  Vector *tokens = lexer->token_vec;
  
  //should create a vector_size function that returns how many elements are in the vecto.
  printf("%s\n",input);
  for(int i = 0; i<20;i++){
    Token *token = vector_at(tokens,i);
    printf("Token %d: Type: %d, Literal: %s\n", i, token->type, token->literal);
  }

  lexer_clean(lexer);
}
