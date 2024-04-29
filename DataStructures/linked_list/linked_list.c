//
// Created by lucas on 4/28/24.
//

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

Node *create_node(void *elem){
  Node *node = malloc(sizeof(Node));
  node->value = elem;
  node->next = NULL;
  
  return node;
}

List *new_list(){
  List *list = malloc(sizeof(List));
  list->head = list->tail = NULL;
  return  list;
}

void list_destroy(List *lptr){
  Node *current = lptr->head;
  Node *next;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  free(lptr);
}

void push_front(List *lptr, void *elem){
  Node *node = create_node(elem);
  if (is_empty(lptr)) {
    lptr->head = lptr->tail =node;
  } else {
    node->next = lptr->head;
    lptr->head = node;
  }
}

void push_back(List *lptr, void *elem){
  Node *node = create_node(elem);
  if (is_empty(lptr)) {
    lptr->head = lptr->tail = node;
  } else {
    lptr->tail->next = node;
    lptr->tail = node;
  }
}

size_t list_size(List *lptr){
  size_t count= 0;
  Node *current = lptr->head;
  while(current!=NULL){
    count++;
    current = current->next;
  }
  return count;
}


bool is_empty(List *lptr){
  return (lptr->head==NULL);
}

void *front(List *lptr){
  return lptr->head->value;
}
void *back(List *lptr){
  return lptr->tail->value;
};

void *value_at(List *lptr,size_t index){
  //check that index is in bounds 
  if (index > list_size(lptr)) {
    perror("index out of bounds");
  } else if (is_empty(lptr)) {
    return NULL;
  } else {
    Node *current = lptr->head;
    size_t c = 0;
    while (current != NULL && c < index) {
      current = current->next;
      c++;
    }
    return current->value;
  } 
}


void *pop_front(List *lptr){
  if (is_empty(lptr)) {
    return NULL;
  }else {
    //store reference to current node
    Node *temp = lptr->head;
    //store the value
    void *value = temp->value;
    //update the head pointer
    lptr->head = lptr->head->next;
    //if the list becomes empty after popping the elemet
    //update tail pointer
    if(lptr->head == NULL){
      lptr->tail = NULL;
    }
    free(temp);
    return value;
  }
}

void *pop_back(List *lptr){
  if (is_empty(lptr)) {
    return NULL;
  } else {
    void *value;
    if(lptr->head == lptr->tail){
      value = lptr->head->value;
      free(lptr->head);
      lptr->head=lptr->tail=NULL;
    }else{
      Node *temp = lptr->head;
      while(temp->next != lptr->tail){
        temp = temp->next;
      }
      value = lptr->tail->value;
      free(lptr->tail);
      lptr->tail=temp;
      lptr->tail->next = NULL;
    }
    return  value;
  }
}

void insert_at(List *lptr,size_t index,void *elem){
 if (index == 0) {
  push_front(lptr, elem);
 }else {
    Node *current= lptr->head;
    Node *newNode = create_node(elem); 
    size_t count = 0;
    while(current!= NULL && count < index-1){
      current = current->next;
      count++;
    }
    //insert the newNode bewten current and current->next
    newNode->next = current->next;
    current->next = newNode;
    
    if(newNode->next == NULL){
      lptr->tail = newNode;
    }
 }

}

void print_list(List *lptr){
  Node *current = lptr->head;
  while (current!=NULL) {
    printf("%d ",*(int*)current->value);
    current=current->next;
  }
  printf("\n");
}



void remove_element(List *lptr , void *elem){
    Node *current = lptr->head;
    Node *prev = NULL;

    // Traverse the list until finding the node with the specified element
    while (current != NULL && current->value != elem) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        // Element not found in the list
        return;
    }

    if (prev == NULL) {
        // If the element to remove is the first node
        pop_front(lptr);
    } else {
        // Remove the node containing the element
        prev->next = current->next;

        // Update the tail pointer if the last node is removed
        if (prev->next == NULL) {
            lptr->tail = prev;
        }

        free(current); // Free the memory of the removed node
    }
}


void erase(List *lptr, size_t index) {
     if (index >= list_size(lptr)) {
        // If index is out of bounds, print an error or handle it accordingly
        perror("Index out of bounds");
        return;
    }

    if (index == 0) {
        // If removing the first element, simply pop_front
        pop_front(lptr);
        return;
    }

    Node *current = lptr->head;
    size_t count = 0;

    // Traverse the list until reaching the node before the specified index
    while (current != NULL && count < index - 1) {
        current = current->next;
        count++;
    }

    // Remove the node at index
    Node *temp = current->next;
    current->next = temp->next;

    // Update the tail pointer if the last node is removed
    if (current->next == NULL) {
        lptr->tail = current;
    }

    free(temp); // Free the memory of the removed node
} 



//find return the node where it is found elem
Node* find(List *lptr,void *elem){
  Node *current = lptr->head;
  while(current!=NULL && current->value != elem){
    current = current->next;
  }
  return current;
}
