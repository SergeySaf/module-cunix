#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "linked_list.h"

 
hashtable_t   *hash_create(unsigned int size)
{
  hashtable_t *hash_table;

  if(size <= 0)
    return NULL;
  else
  {
    hash_table = (hashtable_t*)malloc(sizeof(hashtable_t));
    hash_table -> size = size;
    hash_table -> table = (void**)malloc(size*sizeof(void*));
    for(int i = 0; i < size; i++)
      hash_table->table[i] = NULL;
    return hash_table;
  }
}


void    hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
   node_t *nd;
  for(int i = 0; i < ht->size; i++)
  {
    if(ht->table[i] != NULL)
    {
      nd = ht->table[i];
      list_destroy(&nd, fp);
    }
  }

  free(ht->table);
  ht->table = NULL;
  free(ht);
}


unsigned int    hash_func(char *key)
{
  if(key == NULL)
    return 0;
 int i=0;
 int hash=0;
 while(key[i] != '\0')
  {
    hash += (int)key[i];
    i++;
  }
return hash;
} 


void    hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data))
{
  int tmp = hash_func(key) % ht -> size;

  if(ht -> table[tmp] == NULL)
    ht -> table[tmp] = list_create(ptr);
  else
    list_push(ht -> table[tmp], ptr);

  fp(key);
}


void    *hash_get(hashtable_t *ht, char *key)
{
  int tmp = hash_func(key) % ht -> size;
   
  if(ht -> table[tmp] == NULL)
    return NULL;
  else
    return ((node_t*)ht -> table[tmp]) -> data;
}

