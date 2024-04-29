#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void run_tests() {
    // Create a new list
    List *list = new_list();

    // Insert elements into the list
    int a = 10, b = 20, c = 30, d = 40;
    push_back(list, &a);
    push_back(list, &b);
    push_back(list, &c);
    push_back(list, &d);

    printf("Original list: ");
    print_list(list);
    
    printf("reversed list: ");
    reverse_list(list);
    print_list(list);
  
    //value n from end run_tests
    printf("Value at 2nd position from end: %d\n", *(int*)value_n_from_end(list, 2));
    printf("Value at 4th position from end: %d\n", *(int*)value_n_from_end(list, 3));
    printf("Value at 1st position from end: %d\n", *(int*)value_n_from_end(list, 1));

 
    // Insert an element at a specific index
    int e = 25;
    insert_at(list, 2, &e);
    printf("List after inserting element at index 2: ");
    print_list(list);
    
    
    // Remove a specific element
    remove_element(list, &c);
    printf("List after removing element 30: ");
    print_list(list);

    // Erase an element at a specific index
    erase(list, 1);
    printf("List after erasing element at index 1: ");
    print_list(list);

    // Destroy the list to free memory
    list_destroy(list);
}

int main() {
    run_tests();
    return 0;
}

