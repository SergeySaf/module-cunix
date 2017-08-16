#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"




//Create and Destroy will malloc and free the linked list.
node_t *list_create(void *data)
{
node_t *first_nod = (node_t*)malloc(sizeof(node_t));
first_nod -> data = data;
first_nod -> next = NULL;
return first_nod;
}

void list_destroy(node_t **head, void (*fp)(void *data))
{
  if((*head) == NULL)
  return;
  if((*head) -> next)
    list_destroy(&((*head) -> next), fp);
    fp((*head) -> data);
    free(*head);
    *head == NULL;
}
//////////////////////////////////////////////////////



//Push and unshift will respectively add an element by the end and begining
void list_push(node_t *head, void *data)
{
  node_t* current = head;
  while(current->next != NULL)
    current = current->next;
  current->next = list_create(data);
  current->next->next = NULL;
}
void list_unshift(node_t **head, void *data)
{
  node_t* current = list_create(data);
  current->next = *head;
  *head = current;
}
//////////////////////////////////////////////////////


//Those functions will remove elements by the end, begining and by a pointer
void *list_pop(node_t **head)
{
    if((*head)->next == NULL)
    {
      void *data = (*head)->data;
      free(*head);
      head = NULL;
      return data;
    }
  node_t *current;
  current = *head;
  while (current->next->next != NULL) current = current->next;
  void *data = current->next->data;
  if (current->next->data) free(current->next->data);
  free(current->next);
  current->next = NULL;
  return data;
}
void *list_shift(node_t **head)
{
  node_t *current = *head;
  *head = (*head)->next;
  free(current->data);
  free(current);
  current = NULL;
}
void *list_remove(node_t **head, int pos)
{
  node_t *current;
  current  = *head;
  for(int i = 0; i<pos-1; i++)
  {
    if(current->next->next == NULL) return NULL;
    current = current->next;
  }
  void *data = current->next->data;
  node_t *ptr;
  ptr = current->next;
  current->next = current->next->next;
  free(ptr->data);
  free(ptr);
  ptr = NULL;
  return data;
}
//////////////////////////////////////////////////////



//You can visit an entire list and apply a function fp
void list_print(node_t *head)
{
  node_t* current = head;
  while(current != NULL)
  {
    printf("%s  ", current->data);
    current = current->next;
  }
  free(current);
}
void list_visitor(node_t *head, void (*fp)(void *data))
{
  node_t  *current;
  current = head;
  while(current != NULL)
  {
    fp(current->data);
    current = current->next;
  }
}
//////////////////////////////////////////////////////
