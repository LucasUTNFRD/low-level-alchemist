//
// Created by lucas on 5/1/24.
//

#ifndef HASHMAP_HASHMAP_H
#define HASHMAP_HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

typedef struct Hashmap_Node{
    char *key;
    void *value;
    struct Hashmap_Node *next;
} Hashmap_Node;

typedef struct {
    Hashmap_Node **hashmap;
    int size;

} Map;

int hash_function(char *key,size_t size);
Map *new_map(size_t size);
void destroy_map(Map *map);
void map_add(Map *map, char *key,void*value);
bool map_exists(Map *map,char *key);
Hashmap_Node *map_get(Map *map,char *key);
void map_remove(Map *map, char *key);




#endif //HASHMAP_HASHMAP_H
