#include "hashtable.h"
#include <stdlib.h>


Map *map_new(void){
  Map *map = malloc(sizeof(Map));
  map->length=0;
  map->capacity = HASHMAP_SIZE;
  map->hashmap =malloc(sizeof(map_entry)*map->capacity);

  return map;
}

void map_delete(Map* map){
  //free alocated keys
  for(size_t i = 0;i < map->capacity;i++){
    free((*void)map->hashmap[i].key);
  }
  free(map->hashmap);
  free(map);
}

size_t hash(char *s){

}


void map_insert(Map *map,char* key,void* val){
  size_t index = hash(key);

}

void* map_get(Map* map,char* key);


