// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;

  return mylist;
}

void list_free(list_t *l) {
  node_t *curr = l->head;

  while (curr != NULL) {
    node_t *next = curr->next;
    free(curr);
    curr = next;
  }

  free(l);
}

void list_print(list_t *l) {
  node_t* curr = l->head;

  while(curr != NULL){
    printf("%d->", curr->value);
    curr = curr->next;
  }

  printf("NULL\n");

}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  char tbuf[20];

  buf[0] = '\0';

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;


}
//done 
int list_length(list_t *l) { 
  int count = 0; 
  node_t *curr = l-> head;
  
  while (curr != NULL) {
    count++;
    curr = curr -> next;


  }

  
  return count; }

void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = getNode(value);

  if(l->head == NULL){
    l-> head = new_node;
    return;
  }

  node_t *curr = l->head;

  while (curr -> next != NULL){
    curr = curr->next;
  }

  curr->next = new_node;
}

void list_add_to_front(list_t *l, elem value) {
     node_t *cur_node = (node_t *) getNode(value);

     /* Insert to front */
     node_t *head = l->head;  // get head of list

     cur_node->next = head;
     l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  if (index == 1 ){
    list_add_to_front(l, value);
    return; 
  }

  node_t *new_node = getNode(value);
  node_t *curr = l->head; 

  int i = 1;
  while (curr != NULL && i < index - 1){
    curr = curr->next;
    i++;
  }
  
  if (curr == NULL){
    free(new_node);
    return;

  }

  new_node->next = curr->next;
  curr->next = new_node;
}

elem list_remove_from_back(list_t *l) {
  if (l->head == NULL){
    return -1;
  }

  if (l->head->next == NULL){
    elem value = l->head->value;
    free(l->head);
    l->head = NULL;
    return value; 
  }
  
  node_t *curr = l->head; 

  while (curr->next->next != NULL){
    curr = curr->next;
  }
  
  elem value = curr->next->value;
  free(curr->next);

  curr->next = NULL;

  
  
  return value; }
elem list_remove_from_front(list_t *l) { 
  if (l->head == NULL){
    return -1;
  }

  node_t *temp = l->head;
  l->head = l->head->next;

  elem value = temp->value;
  free(temp);

  return value;
}
elem list_remove_at_index(list_t *l, int index) {
  if (l == NULL || l->head == NULL || index < 1){
    return -1;
  } 

  if (index == 1){
    node_t *temp = l->head;
    elem value = temp->value;
    
    l->head = temp->next; 
    free(temp);

    return value;
  }
  
  node_t *curr = l->head;
  for (int i = 1; i < index -1; i++){
    if (curr->next == NULL){
      return -1;
    }
    curr = curr->next;
  }

  if(curr->next == NULL){
    return -1;
  }

  node_t *temp = curr->next;
  elem value = temp->value;

  curr->next = temp->next;

  free(temp);
  return value;
   }

bool list_is_in(list_t *l, elem value) { 
  node_t *curr = l->head;

  while(curr != NULL){
    if(curr->value == value){
      return true;

    }
    curr = curr->next;
  }  
  
  
  
  return false; }
elem list_get_elem_at(list_t *l, int index) {
  if (index < 1){
    return -1;
  }
  node_t *curr = l->head;
  int count = 1;

  while (curr != NULL){
    if (count == index){
      return curr->value; 
    }
    curr = curr->next;
    count++;
  }
  
  
  
  return -1; }
int list_get_index_of(list_t *l, elem value) {
  int index = 1; 
  node_t *curr = l->head;

  while (curr != NULL){
    if (curr->value == value){
      return index;
    }

    curr = curr->next;
    index++;
  }
  
  
  
  return -1; }

