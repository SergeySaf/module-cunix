#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "filler.h"
#include "stream.h"

elem_t *create_elem()
{
  elem_t *elem;

  elem = malloc(sizeof(elem_t));
  elem->fig_w = 0;
  elem->fig_h = 0;
  elem->figure = NULL;
  return elem;
}

void destroy_elem(elem_t *elem)
{
  if (elem->figure)
  {
    for(int i = 0; i < elem->fig_h; i++)
        free(elem->figure[i]); 
    free(elem->figure);
  }
  free(elem);
}

