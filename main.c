#include "lexer.h"

int main() {
    const char* input = "Your input string here";
    struct Lexer* lexer = lexer_create(input);

    // Use the lexer...

    // Don't forget to free the memory when you're done
    // implement some free function for the lexer structure 
    return 0;
}

