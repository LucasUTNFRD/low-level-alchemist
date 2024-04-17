#ifndef HT_H
#define HT_H

//API design
#include <stdlib.h>
#include "vector.h"
#include "types.h"
#define HASHMAP_SIZE 16

typedef struct map_entry{
  char *key;
  TokenType type;
} map_entry;

typedef struct{
  map_entry *hashmap;
  size_t length;
  size_t capacity;
}Map;

Map *map_new();

void map_delete(Map* map);

TokenType map_get(Map* map,char* key);

void map_insert(Map *map,char *key,TokenType type);

#endif // !HT_H
