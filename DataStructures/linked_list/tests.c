#include "tests.h"
#include "linked_list.h"
#include <assert.h>
#include <stdio.h>

void run_all_tests() {
  test_size();
  test_push_front();
  test_empty();
  test_front();
  test_back();
  // test_pop_front();
  test_push_back();
  test_pop_back();
  test_insert();
  test_value_at();
  // test_erase();
  // test_value_n_from_end();
  test_reverse();
  // test_reverse_single();
  // test_reverse_empty();
  // test_remove();
}

void test_size(){
  int size ;
  
  List *test = new_list();
  //test for empty list
  size = list_size(test); 
  assert(size==0);
  //test for non empty list
  int elem = 2;
  push_back(test,&elem);
  assert(list_size(test)==1);
  
  list_destroy(test);
}

void test_push_front(){
  List *test = new_list();
  assert(list_size(test)==0);

  int elem1 = 2, elem2 = 3,elem3 = 7, elem4 = 5;
  push_front(test, &elem1);
  push_front(test, &elem2);
  push_front(test, &elem3);
  push_front(test, &elem4);
  
  assert(list_size(test)==4);
  
  list_destroy(test);
}


void test_push_back(){
  List *test = new_list();
  assert(list_size(test)==0);

  int elem1 = 2, elem2 = 3,elem3 = 7, elem4 = 5;
  push_back(test, &elem1);
  push_back(test, &elem2);
  push_back(test, &elem3);
  push_back(test, &elem4);
  
  assert(list_size(test)==4);
  
  list_destroy(test);
}

void test_empty(){
  List *test = new_list();
  assert(is_empty(test));

  int elem1 = 2;
  push_back(test, &elem1);
  assert(!is_empty(test));

}

void test_front(){
    List *test = new_list();
    int elem1 = 2, elem2 = 3, elem3 = 7, elem4 = 5;
    push_back(test, &elem1);
    push_back(test, &elem2);
    push_back(test, &elem3);
    push_back(test, &elem4);

    assert(*(int*)front(test) == elem1);

    list_destroy(test);
}

void test_back(){
    List *test = new_list();
    int elem1 = 2, elem2 = 3, elem3 = 7, elem4 = 5;
    push_back(test, &elem1);
    push_back(test, &elem2);
    push_back(test, &elem3);
    push_back(test, &elem4);

    assert(*(int*)back(test) == elem4);

    list_destroy(test);
}


void test_insert(){
    List *test = new_list();
    int elem1 = 2, elem2 = 3, elem3 = 7, elem4 = 5;
    push_back(test, &elem1);
    push_back(test, &elem2);
    push_back(test, &elem3);

    insert_at(test, 1, &elem4);
    assert(*(int*)value_at(test, 1) == elem4);

    list_destroy(test);
}

void test_value_at(){
    List *test = new_list();
    int elem1 = 2, elem2 = 3, elem3 = 7, elem4 = 5;
    push_back(test, &elem1);
    push_back(test, &elem2);
    push_back(test, &elem3);
    push_back(test, &elem4);

    assert(*(int*)value_at(test, 2) == elem3);

    list_destroy(test);
}

void test_pop_back(){
  List *test = new_list();
  int elem1 = 2, elem2 = 3, elem3 = 7, elem4 = 5;
  push_back(test, &elem1);
  push_back(test, &elem2);
  push_back(test, &elem3);
  push_back(test, &elem4);

  int popped_elem = *(int*)pop_back(test);
  assert(popped_elem == elem4);

  popped_elem = *(int*)pop_back(test);
  assert(popped_elem == elem3);
  
  popped_elem = *(int*)pop_back(test);
  assert(popped_elem == elem2);

  popped_elem = *(int*)pop_back(test);
  assert(popped_elem == elem1);

  assert(pop_back(test)==NULL);
  
  list_destroy(test);
}

void test_pop_front(){
  List *test = new_list();
  int elem1 = 2, elem2 = 3, elem3 = 7, elem4 = 5;
  push_front(test, &elem1);
  push_front(test, &elem2);
  push_front(test, &elem3);
  push_front(test, &elem4);

  int popped_elem = *(int*)pop_front(test);
  assert(popped_elem == elem1);

  popped_elem = *(int*)pop_front(test);
  assert(popped_elem == elem2);
  
  popped_elem = *(int*)pop_front(test);
  assert(popped_elem == elem3);

  popped_elem = *(int*)pop_front(test);
  assert(popped_elem == elem4);

  assert(pop_front(test)==NULL);
  
  list_destroy(test);
}

void test_reverse() {
    // Test reversing a list with multiple elements
    List *test = new_list();
    int elems[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < sizeof(elems) / sizeof(elems[0]); i++) {
        push_back(test, &elems[i]);
    }

    printf("Original list: ");
    print_list(test);

    // Reverse the list
    reverse_list(test);

    printf("Reversed list: ");
    print_list(test);

    // Verify the reversed list
    int expected[] = {5, 4, 3, 2, 1};
    Node *current = test->head;
    for (int i = 0; i < sizeof(expected) / sizeof(expected[0]); i++) {
        assert(*(int *)current->value == expected[i]);
        current = current->next;
    }

    list_destroy(test);

    // Test reversing an empty list
    List *empty_list = new_list();
    reverse_list(empty_list);
    assert(is_empty(empty_list));
    list_destroy(empty_list);

    // Test reversing a single-element list
    List *single_element_list = new_list();
    int elem = 42;
    push_back(single_element_list, &elem);
    reverse_list(single_element_list);
    assert(*(int *)single_element_list->head->value == 42);
    list_destroy(single_element_list);
}


