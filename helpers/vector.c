#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector* vector_create(size_t esize){
  Vector* vector = malloc(sizeof(Vector));
  vector->data = malloc(esize * VECTOR_INITIAL_SIZE);
  vector->esize = esize;
  vector->modifiedIndex=VECTOR_INITIAL_SIZE;
  vector->readIndex = 0;
  vector->size = 0;

  return vector;
}

void vector_free(Vector *vector){
  free(vector->data);
  free(vector);
}

void vector_resize(Vector *vector){
  size_t newCapacity = vector->modifiedIndex * 2;
  
  void* newData = realloc(vector->data, newCapacity * vector->esize);
  if (newData) {
    vector->data = newData;
  } else {
    printf("Error: unable to resize\n");
    exit(EXIT_FAILURE);
  }
}

void* vector_at(Vector *vector,size_t index){
  return vector->data + (index * vector->esize);
  // This calculates the memory offset where the new element should be copied.
}

void vector_push(Vector *vector, void *element){
  if(vector->size >= vector->modifiedIndex){
    vector_resize(vector);
  }

  void *ptr = vector_at(vector,vector->readIndex);
  memcpy(ptr, element,vector->esize);
  vector->readIndex++;
  vector->size++;
}



