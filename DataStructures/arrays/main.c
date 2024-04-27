#include "array.h"
#include <stdio.h>


int main() {
    // Create a new array to store integers
  Array *arr = new_array(sizeof(int));

    // Load the array with numbers
  int numbers[] = {10, 20, 30, 40, 50, 70,80,1,5};
  size_t num_elements = sizeof(numbers) / sizeof(numbers[0]);
  for (size_t i = 0; i < num_elements; ++i) {
    array_pushback(arr, &numbers[i]);
  }

  // Print the elements of the array
  printf("Elements of the array:\n");
  for (size_t i = 0; i < array_size(arr); ++i) {
    int *element = array_at(arr, i);
    printf("%d ", *element);
  }
  printf("\n");

  int search_value = 3;
  int index = array_find(arr, &search_value, int_cmp_func);
  if (index != -1) {
    printf("El elemento %d se encuentra en el índice %d del array de enteros.\n", search_value, index);
  } else {
    printf("El elemento %d no se encuentra en el array de enteros.\n", search_value);
  }
  int element_to_insert = 69;
  array_insert_at(arr, 2, &element_to_insert);
  // array_insert_at(arr, 2, &element_to_insert);
  // array_insert_at(arr, 2, &element_to_insert);
  // array_insert_at(arr, 2, &element_to_insert);
  // array_insert_at(arr, 2, &element_to_insert);

  printf("Elements of the array post insertion:\n");
  for (size_t i = 0; i < array_size(arr); ++i) {
    int *element = array_at(arr, i);
    printf("%d ", *element);
  }
  printf("\n");
  
  int element_to_prepend = 420;
  array_prepend(arr,&element_to_prepend);
  printf("Elements of the array post prepend:\n");
  for (size_t i = 0; i < array_size(arr); ++i) {
    int *element = array_at(arr, i);
    printf("%d ", *element);
  }
  printf("\n");

  array_delete(arr,0);
  printf("Elements of the array post deletion:\n");
  for (size_t i = 0; i < array_size(arr); ++i) {
    int *element = array_at(arr, i);
    printf("%d ", *element);
  }
  printf("\n");

  int *last_element = array_pop(arr);

  printf("last element in array that was popped: %d\n",*last_element) ;
  printf("Elements of the array post pop:\n");
  for (size_t i = 0; i < array_size(arr); ++i) {
    int *element = array_at(arr, i);
    printf("%d ", *element);
  }

  printf("\n");
  int int_to_remove =69 ; 
  array_remove(arr, &int_to_remove, int_cmp_func);
  printf("Elements of the array post remove:\n");
  for (size_t i = 0; i < array_size(arr); ++i) {
    int *element = array_at(arr, i);
    printf("%d ", *element);
  }

    // Free the memory allocated for the array
  array_free(arr);
    
  return 0;
}
