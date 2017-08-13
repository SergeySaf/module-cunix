#include "my_string.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

stream_t        *string_init()
{
  stream_t      *s;

  s = (stream_t*) malloc(sizeof(stream_t));
  s->str = NULL;
  s->size = 0;
  s->limit = 0;

  return s;
}

stream_t        *string_create(char* str)
{
  stream_t      *s;
  int           size;
  int           q;

  size = strlen(str);
  q = size / BUF_SIZE + 1;
  s = string_init();
  s->str = (char*) malloc (q * BUF_SIZE * sizeof(char));
  strcpy(s->str, str);
  s->size = size;
  s->limit = q * BUF_SIZE;

  return s;
}

void            string_add(stream_t* ptr, char* str)
{
  int           size_str;

  size_str = strlen(str);

  for(int i = 0; i < size_str; i++)
    ptr->str[ptr->size + i] = str[i];

  ptr->size += size_str;
  ptr->str[ptr->size] = 0;
}

void        string_append(stream_t *ptr, char* str)
{
  int           size;

  if(ptr == NULL)
  {
    ptr = string_create(str);
  }
  else
  {
    size = strlen(str);
    if(ptr->size + size >= ptr->limit)
    {
      ptr->str = (char*) realloc (ptr->str, ptr->limit + 4 * BUF_SIZE);
      ptr->limit += 4 * BUF_SIZE;
      ptr->str[ptr->size + size] = 0;
    }
   string_add(ptr, str);
  }
}

void            string_destroy(stream_t *s)
{
  free(s->str);
  free(s);
  s = NULL;
}
