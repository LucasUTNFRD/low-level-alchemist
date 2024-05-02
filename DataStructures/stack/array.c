#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función de comparación para enteros
int int_cmp_func(const void *a, const void *b) {
    const int *pa = (const int *)a;
    const int *pb = (const int *)b;
    return (*pa > *pb) - (*pa < *pb);
}

// Función de comparación para cadenas de caracteres
int str_cmp_func(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}



Array *new_array(size_t esize){
  Array *arr = malloc(sizeof(Array));
  arr->esize = esize;
  arr->capacity = INITIAL_SIZE;
  arr->items = malloc(arr->capacity * arr->esize);
  arr->size = 0;

  return arr;
  
}
void array_free(Array* arr){
  free(arr->items);
  free(arr);
}

size_t array_size(Array *arr){
  return arr->size;
}

size_t array_capacity(Array *arr){
  return arr->capacity;
}

bool isEmpty(Array *arr){
  return arr->size == 0;
}

bool array_in_bounds(Array *arr,size_t index){
  return (index < arr->size && index >= 0);
}

/*  The array_at(arr, arr->size) function likely returns a pointer to the position at the end of the array. */
/*to check what is array at we need to dereference the pointer */
void *array_at(Array *arr,size_t index){
  return arr->items + (index * arr->esize);
}



//when capacity is reached, resize to double the size 
//when popping an item, if the size is 1/4 of capacity resize to half
void array_resize_for_size(Array *arr, size_t candidate_size){
  if (candidate_size > arr->size) { /*grow */
    if(arr->size == arr->capacity){
      array_upsize(arr);
    }
  } else if (candidate_size < arr->size) {/*shrink */
      if(arr->size <= arr->capacity / DOWNSIZE_FACTOR)
        array_downsize(arr);
  }
  
}

void array_upsize(Array *arr){
  size_t oldCapacity = array_capacity(arr);
  size_t newCapacity = oldCapacity * UPSIZE_FACTOR;
  void *new_items = malloc(arr->esize*newCapacity);
  new_items = arr->items;
  arr->items = new_items;
  arr->capacity = newCapacity;

}


void array_downsize(Array *arr){
  size_t oldCapacity = array_capacity(arr);
  size_t newCapacity = oldCapacity / DOWNSIZE_FACTOR;
  
  // Ensure that the new capacity doesn't become less than the initial size
  if (newCapacity < INITIAL_SIZE) {
    newCapacity = INITIAL_SIZE;
  }

  // Only downsize if the new capacity is significantly smaller than the old capacity
  if (newCapacity < oldCapacity / 2) {
    void *new_items = realloc(arr->items, newCapacity * arr->esize);
    if (new_items != NULL) {
      arr->items = new_items;
      arr->capacity = newCapacity;
    }
  }
}

void array_pushback(Array *arr, void *elem){
  // Check if we need to resize the array
  array_resize_for_size(arr, arr->size + 1);
  
  // Copy the new element to the array
  void *destination = array_at(arr, arr->size);
  memcpy(destination, elem, arr->esize);
  
  arr->size++;
}


//support comparicion bewten char* and int;
int array_find(Array *arr, void *elem, int (*cmp_func)(const void *, const void *)){
  for (size_t i = 0; i < array_size(arr); i++) {
    if (cmp_func(array_at(arr, i), elem) == 0) {
      return i; // Element found
    }
  }
  return -1; // Element not found
}

void array_insert_at(Array *arr,size_t index,void *elem){
  //check if index is in array in bounds;
  if (!array_in_bounds(arr,index)){
    perror("Array not in bounds");
  }
  //check if for new size is needed a resize
  array_resize_for_size(arr,arr->size+1);
  //shift elements to right
  shift_right(arr,index);
  //insert element at especified index
  void *destination = array_at(arr, index);
  memcpy(destination,elem,arr->esize);
  //increment size
  arr->size++;
}

void shift_right(Array *arr,size_t index){
  //shift elements to right
  for (size_t i = arr->size; i > index; --i) {
      void *destination = array_at(arr, i);
      void *source = array_at(arr, i - 1);
      memcpy(destination, source, arr->esize);
   }
}

void shift_left(Array *arr,size_t index){
  //shift elements to left 
  for (size_t i = index ;i<arr->size;i++) {
      void *destination = array_at(arr, i);
      void *source = array_at(arr, i + 1);
      memcpy(destination, source, arr->esize);
   }
}

void array_delete(Array *arr,size_t index){
  if (!array_in_bounds(arr,index)){
    perror("Array not in bounds");
  }
  //check if for new size is needed a resize
  array_resize_for_size(arr,arr->size-1);

  shift_left(arr, index);
  
  arr->size--;
}


// Prepending an element to an array means inserting the element at the beginning of the array, shifting all existing elements to the right, and increasing the size of the array by one. Essentially, it's adding an element to the front of the array.
void array_prepend(Array *arr,void *elem){
 //check if resize needed 
  array_resize_for_size(arr,arr->size+1);

  size_t index = 0;
  shift_right(arr,index);
  //insert element at especified index
  void *destination = array_at(arr, index);
  memcpy(destination,elem,arr->esize);

}

void *array_pop(Array *arr){
  if(arr->size == 0){
    exit(EXIT_FAILURE);
  }
  
  array_resize_for_size(arr,arr->size-1);

  void *popped_val = array_at(arr,arr->size-1);

  arr->size--;
  
  return popped_val;

}


void array_remove(Array *arr, void *elem, int (*cmp_func)(const void*, const void*)) {
    // Check if resize is needed
    if (arr->size == 0) {
        return;  // Nothing to remove
    }

    // Check if element is in array
    for (size_t i = 0; i < array_size(arr); ) {
        if (cmp_func(array_at(arr, i), elem) == 0) {
            array_delete(arr, i);
        } else {
            ++i;
        }
    }
}

