#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "filler.h"
#include "stream.h"

filler_t *create_filler()
{
  filler_t *filler;

  filler = malloc(sizeof(filler_t));
  filler->symbol = '*';
  filler->w = 0;
  filler->h = 0;
  filler->map = NULL;
  filler->prev_map = NULL;
  return filler;
}

void destroy_filler(filler_t *filler)
{
  if (filler->map)
  {
    for(int i = 0; i < filler->h; i++)
          free(filler->map[i]); 
     free(filler->map);
  }
  if (filler->prev_map)
  {
    for(int i = 0; i < filler->h; i++)
          free(filler->prev_map[i]); 
    free(filler->prev_map);
  }
  free(filler);
}

