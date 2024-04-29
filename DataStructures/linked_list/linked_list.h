//
// Created by lucas on 4/28/24.
//

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    void *value;
    struct Node *next;
} Node;

typedef struct List{
    Node *head;
    Node *tail;
}List;

//basic API
Node *create_node(void *elem);
void list_destroy(List *lprt);
List *new_list(void);
void push_front(List *lptr,void *elem);
void push_back(List *lptr, void *elem);
bool is_empty(List *lptr);
void *front(List *lptr);
void *back(List *lptr);
void *pop_front(List *lptr);
void *pop_back(List *lptr);
Node *find(List *lptr,void *elem);
size_t list_size(List *lptr);
void *value_at(List *lptr,size_t index);
void erase(List *lptr,size_t index);
void insert_at(List *lptr,size_t index,void *elem);
void reverse_list(List *lptr);
void remove_element(List *lprt,void *elem);
void print_list(List *lptr);


#endif //LINKED_LIST_H
