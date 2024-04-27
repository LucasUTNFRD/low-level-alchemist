#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/vector.h"

// Function to read the contents of a file and return it as a string
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0'; // Null-terminate the string
    fclose(file);

    return buffer;
}

int main() {
    // Read the contents of the .c file
    const char* filename = "input.lox";
    char* input = read_file(filename);

    // Create a lexer
    Lexer* lexer = lexer_create(input);

    // Tokenize the input
    lexer_tokenize(lexer);
    Vector* tokens = lexer->token_vec;

    // Print the tokens
    printf("Tokens from %s:\n", filename);
    for (int i = 0; i < vector_size(tokens); i++) {
        Token* token = vector_at(tokens, i);
        printf("Token %d: Type: %d, Literal: %s\n", i, token->type, token->literal);
    }

    //implement parsing logic.
    Parser* parser = parse(tokens);
    if(parser->status == COMPILED_FINE){
      puts("everything compiled fine");
    }ELSE{
      puts("Compilation error");
    }

    // Clean up
    lexer_clean(lexer);
    free(input); // Free the memory allocated for the input

    return 0;
}

