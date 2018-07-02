#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filler.h"
#include "stream.h"

int cell_inside_map(int x, int y, filler_t *filler, elem_t *elem)
{
  return (x < filler->w) && (x >= 0) && (y < filler->h) && (y >= 0);
}

int cell_is_empty(int x, int y, filler_t *filler, elem_t *elem)
{
  return filler->map[y][x] == '.';
}

int cell_is_nghbr(int x, int y, filler_t *filler, elem_t *elem){
  return filler->map[y][x] == filler->symbol;
}

int cell_nghbr_exist(int x, int y, filler_t *filler, elem_t *elem)
{
  if(cell_inside_map(x, y+1, filler, elem) && cell_is_nghbr(x, y+1, filler, elem))
    return 1;
  if(cell_inside_map(x, y-1, filler, elem) && cell_is_nghbr(x, y-1, filler, elem))
    return 1;
  if(cell_inside_map(x+1, y, filler, elem) && cell_is_nghbr(x+1, y, filler, elem))
    return 1;
  if(cell_inside_map(x-1, y, filler, elem) && cell_is_nghbr(x-1, y, filler, elem))
    return 1;
  return 0;
}

int can_put_figure(int x, int y, filler_t *filler, elem_t *elem)
{
  int neigh_found;
      
  neigh_found = 0;
  for(int i = 0; i < elem->fig_h; i++)
    for(int j = 0; j < elem->fig_w; j++)
      if(elem->figure[i][j] == '*')
      {
         if(!cell_inside_map(x+j, y+i, filler, elem))
           return 0;
         if(!cell_is_empty(x+j, y+i, filler, elem))
           return 0;
         if(cell_nghbr_exist(x+j, y+i, filler, elem))
            neigh_found = 1;
      }
  return neigh_found;
}


pos_t direction(filler_t *filler, elem_t *elem, int dir)
{
  pos_t res;
  int w, h; 
    
  w = filler->w;
  h = filler->h;
  if(dir % 4 == 1)
  {
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++)
        if(can_put_figure(j, i, filler, elem))
        {
          res.x = j;
          res.y = i;
          return res;
        }
  }
  else if (dir % 4 == 3)
  {
    for (int i = h - 1; i >= 0; i--)
      for (int j = 0; j < w; j++)
        if(can_put_figure(j, i, filler, elem))
        {
          res.x = j;
          res.y = i;
          return res;
        }
  }
  else if (dir % 4 == 2) 
  {
    for (int j = w - 1; j >= 0; j--)
      for (int i = 0; i < h; i++)
        if(can_put_figure(j, i, filler, elem))
        {
          res.x = j;
          res.y = i;
          return res;
        }
  }
  else if (dir % 4 == 0)
  {
    for (int j = w - 1; j >= 0; j--)
      for (int i = h - 1; i >= 0; i--)
        if(can_put_figure(j, i, filler, elem))
        {
          res.x = j;
          res.y = i;
          //dir++;
          return res;
        }
  } 
}

int elem_is_wall(filler_t *filler, elem_t *elem, int x, int y)
{
  if((x == 0) || (y == 0) || (x == filler->w - 1) || (y == filler->h - 1))
    return 1;
  else
    return 0; 
}

int wall_reached(filler_t *filler, elem_t *elem, pos_t pos)
{
  for(int i = 0; i < elem->fig_h; i++)
    for(int j = 0; j < elem->fig_w; j++)
      if(elem->figure[i][j] == '*')
        if(elem_is_wall(filler, elem, pos.x+j, pos.y+i))
          return 1;
  return 0;
}

pos_t start(filler_t *filler, elem_t *elem)
{
    pos_t res;
    static int dir = 1;

    res = direction(filler, elem, dir);
    
    if(res.x < 0) // no matches found
      return res;
    
    if(wall_reached(filler, elem, res))
      dir++;
    return res;
}

pos_t play(filler_t *filler, elem_t *elem)
{
    return start(filler, elem);
}

