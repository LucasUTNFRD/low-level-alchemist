#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// i want 20 vectors element space in memory at least
// before reallocate memory again
#define VECTOR_INITIAL_SIZE 20

typedef struct{
  void* data;//generic pointer to make it generic data type
  size_t size;
  size_t readIndex;
  size_t modifiedIndex; // aux var for reallocate memory
  size_t esize;
} Vector;

Vector* vector_create(size_t esize);
void vector_free(Vector* vector);
void vector_push(Vector *vector,void *element);
void vector_resize(Vector *vector);
void vector_get(Vector *vector, size_t index);
void* vector_at(Vector *vector,size_t index);


#endif // !VECTOR_H
