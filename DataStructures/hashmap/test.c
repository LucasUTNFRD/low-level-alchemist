//
// Created by lucas on 5/1/24.
//
#include "test.h"
#include <stdlib.h>
#include <stdio.h>


void run_all_test(){
    test_map_add();
    test_map_remove();
    test_map_update();
}

void test_map_add() {
    Map *map = new_map(100);
    int value = 42;
    map_add(map, "key", &value);
    assert(*(int *)map_get(map, "key")->value == 42);
    destroy_map(map);
}

void test_map_update() {
    Map *map = new_map(100);
    int value1 = 42;
    int value2 = 100;
    map_add(map, "key", &value1);
    map_add(map, "key", &value2);
    assert(*(int *)map_get(map, "key")->value == 100);
    destroy_map(map);
}

void test_map_remove() {
    Map *map = new_map(100);
    int value = 42;
    map_add(map, "key", &value);
    map_remove(map, "key");
    assert(map_get(map, "key") == NULL);
    destroy_map(map);
}