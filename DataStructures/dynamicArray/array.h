#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

#define ARRAY_INITIAL_CAPACITY 16

//we need a macro to get the type of the element;
#define array(T, a) array_init(sizeof(T), ARRAY_INITIAL_CAPACITY, a)

typedef struct {
    void *(*alloc)(size_t bytes, void *context);
    void *(*free)(size_t bytes, void *ptr, void *context);
    void *context;
} Allocator;

typedef struct{
  size_t length;
  size_t capacity;
  size_t padding;
  Allocator *a;
}Array_header;

void *array_init(size_t itemSize,size_t capacity,Allocator *a);

//Allocator functions
void *my_alloc(size_t bytes, void *context);
void *my_free(size_t bytes, void *ptr, void *context);

#endif // !ARRAY_H

