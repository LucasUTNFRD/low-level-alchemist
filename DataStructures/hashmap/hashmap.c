//
// Created by lucas on 5/1/24.
//

#include "hashmap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int hash_function(char *key,size_t size){
    int hash = 0;
    for(size_t i = 0;key[i]!='\0';i++){
        hash += key[i];
    }
    return hash % size;
}

Map *new_map(size_t size){
    Map *map = malloc(sizeof(Map));
    map->size = size;
    map->hashmap = malloc(sizeof(Hashmap_Node) * size);
    for(size_t i=0;i<size;i++){
        map->hashmap[i] = NULL;
    }

    return map;
}

void destroy_map(Map *map){
    size_t size = map->size;
    for(size_t i=0;i<size;i++){
        Hashmap_Node *node =map->hashmap[i];
        Hashmap_Node *next;
        while(node!=NULL){
            next=node->next;
//            free(node->value);
            free(node->key);
            free(node);
            node = next;
        }
    }
    free(map->hashmap);
    free(map);
}


void map_add(Map *map, char *key,void*value){
    int index = hash_function(key,map->size);

    //check if key is already in map
    Hashmap_Node *node = map_get(map,key);
    if(node != NULL){
//        free(node->value);
        node->value = value;
        return;
    }

    //if key not found
    //create a node with key and val
    node = malloc(sizeof(Hashmap_Node));
    node->key = strdup(key);
    node->value = value;
    node->next = map->hashmap[index];
    map->hashmap[index] = node;

}
bool map_exists(Map *map,char *key){
    Hashmap_Node *node = map_get(map, key);
    return node != NULL;
}


Hashmap_Node *map_get(Map *map ,char *key){
    int index = hash_function(key,map->size);
    Hashmap_Node *node = map->hashmap[index];
    while(node!=NULL){
        if(strcmp(node->key,key)==0){
            return node;
        }
        node =node->next;
    }
    return NULL;
}

void map_remove(Map *map, char *key) {
    int index = hash_function(key, map->size);

    // Get a reference to the head of the linked list
    Hashmap_Node *current = map->hashmap[index];
    Hashmap_Node *prev = NULL;

    // Search for the node with the given key
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            // Node found, remove it from the list
            if (prev == NULL) {
                // Node to remove is the head of the list
                map->hashmap[index] = current->next;
            } else {
                // Node to remove is not the head of the list
                prev->next = current->next;
            }
            // Free memory allocated for key, value, and the node itself
            free(current->key);
//            free(current->value);
            free(current);
            return;
        }
        // Move to the next node
        prev = current;
        current = current->next;
    }
}


