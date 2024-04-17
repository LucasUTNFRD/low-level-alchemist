#include "hashtable.h"
#include "types.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Map *map_new(){
  Map *map = malloc(sizeof(Map));
  map->length = 0;
  map->capacity = HASHMAP_SIZE;  
  map->hashmap=malloc(sizeof(map_entry)*map->capacity);
  return map;
}


void map_delete(Map* map){
  for (size_t i =0 ;i<map->capacity;i++) {
    free(map->hashmap[i].key);
  }
  free(map->hashmap);
  free(map);
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key,Map *map) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash % map->capacity;
}


void map_insert(Map *map, char *key, TokenType type){
  uint64_t hash= hash_key(key,map);
  size_t index = (size_t)hash; 
  //loop till we find a empty space
  while (map->hashmap[index].key !=NULL) {
    if(strcmp(key,map->hashmap[index].key )==0){
      //update value
      map->hashmap[index].type=type;
    }
    index = (index + 1) % map->capacity;
  }
  map->hashmap[index].key = strdup(key); // Make a copy of the key
  map->hashmap[index].type= type;
  map->length++; // Increase the length of the map
}

TokenType map_get(Map *map, char *key){
  
  uint64_t hash= hash_key(key,map);
  size_t index = (size_t)hash; 
  while (map->hashmap[index].key !=NULL) {
    if(strcmp(key,map->hashmap[index].key )==0){
      //update value
      return map->hashmap[index].type;
    }
    index = (index + 1) % map->capacity;
  }
  return -1;
}
