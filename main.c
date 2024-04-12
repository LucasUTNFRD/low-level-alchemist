#include "lexer.h"
#include "helpers/vector.h"
#include <stdio.h>

int main() {
  const char *input = "( )";
  Lexer* lexer = lexer_create(input);

  lexer_tokenize(lexer);
  
  Vector *tokens = lexer->token_vec;

  printf("Tokens: \n");
  for(int i = 0; i<4;i++){
    Token *token = vector_at(tokens,i);
    printf("Token %d: Type: %d, Literal: %s\n", i, token->type, token->literal);
  }

  lexer_clean(lexer);
}
