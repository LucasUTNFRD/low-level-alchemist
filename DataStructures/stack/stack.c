//
// Created by lucas on 5/1/24.
//

// program to check valid parentheses using a STACK

#include "array.h"
#include <stdbool.h>

// Function to check if a character is an opening parenthesis
bool isOpeningParenthesis(char c) {
    return (c == '(' || c == '[' || c == '{');
}

// Function to check if a character is a closing parenthesis
bool isClosingParenthesis(char c) {
    return (c == ')' || c == ']' || c == '}');
}

// Function to check if two parentheses form a valid pair
bool isValidPair(char opening, char closing) {
    return ((opening == '(' && closing == ')') ||
            (opening == '[' && closing == ']') ||
            (opening == '{' && closing == '}'));
}

// Function to check if a string of parentheses is valid
bool isValidParentheses(char *input) {
    Array *stack = new_array(sizeof(char));

    for (size_t i = 0; input[i] != '\0'; i++) {
        char current = input[i];

        if (isOpeningParenthesis(current)) {
            array_pushback(stack, &current);
        } else if (isClosingParenthesis(current)) {
            if (isEmpty(stack)) {
                array_free(stack);
                return false;  // Closing parenthesis with no matching opening parenthesis
            }
            char *top = array_pop(stack);
            if (!isValidPair(*top, current)) {
                array_free(stack);
                return false;  // Mismatched parentheses
            }
        }
    }

    bool isValidSequence = isEmpty(stack);
    array_free(stack);
    return isValidSequence;
}

int main() {
    char *input1 = "(()";
    if (isValidParentheses(input1)) {
        puts("Input is a valid sequence of parentheses\n");
    } else {
        puts("Input is not a valid sequence of parentheses\n");
    }

    return 0;
}



