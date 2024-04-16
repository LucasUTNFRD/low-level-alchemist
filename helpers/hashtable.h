#ifndef HT_H
#define HT_H

//API design
#define HASHMAP_SIZE 16

//we use a hashmap using lienar probing to use cpu cache optimization, instead of using linked lists.

#include <stdlib.h>

typedef struct map_entry{
  char *key;
  void *value;
} map_entry;

typedef struct{
  map_entry *hashmap;
  size_t length;
  size_t capacity;
}Map;

Map *map_new(void);

void map_delete(Map* map);

void* map_get(Map* map,char* key);


#endif // !HT_H
