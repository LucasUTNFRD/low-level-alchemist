#ifndef ARRAY_H 
#define ARRAY_H

#include <stdio.h>
#include <stdbool.h>
#define INITIAL_SIZE 5 
#define DOWNSIZE_FACTOR 4
#define UPSIZE_FACTOR 2
typedef struct ArrayStruct{
  void *items;
  size_t size,capacity;
  size_t esize; /* element size */ 

}Array ;

void shift_right(Array *arr,size_t index);
void shift_left(Array *arr,size_t index);
Array *new_array(size_t esize);
void array_free(Array *arr);
size_t array_size(Array *arr);
size_t array_capacity(Array *arr);
bool isEmpty(Array *arr);
bool array_in_bounds(Array *arr,size_t index);
void *array_at(Array *arr,size_t index);
void array_pushback(Array *arr,void *elem);
void array_resize_for_size(Array *arr, size_t candidate_size);

void array_upsize(Array *arr);

void array_downsize(Array *arr);

int int_cmp_func(const void *a, const void *b) ;

// Función de comparación para cadenas de caracteres
int str_cmp_func(const void *a, const void *b) ;

int array_find(Array *arr, void *elem, int (*cmp_func)(const void *, const void *));

void array_insert_at(Array *arr,size_t index,void *elem);

void array_delete(Array *arr,size_t index);
// Prepending an element to an array means inserting the element at the beginning of the array, shifting all existing elements to the right, and increasing the size of the array by one. Essentially, it's adding an element to the front of the array.
void array_prepend(Array *arr,void *elem);

void *array_pop(Array *arr);

void array_remove(Array *arr, void *elem, int (*cmp_func)(const void*, const void*)) ;
#endif // !ARRAY_H
