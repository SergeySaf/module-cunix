#include "filler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int check_range(int h, int w, int i, int j)
{
  return (i < h && i >= 0 && j < w && j >= 0);
}

bool find_symbol(map_elem_t *map, int x, int y, char ch) 
{
   return (y + 1 < map->h && map->array[y + 1][x] == ch) ||
          (y - 1 >= 0 && map->array[y - 1][x] == ch) ||
          (x - 1 >= 0 && map->array[y][x -1] == ch) ||
          (x + 1 < map->w && map->array[y][x + 1] == ch);
}

int check_free_space(map_elem_t* map, map_elem_t *elem, pos_t pos)
{
  for (int i = 0; i < elem->h; i++)
    for (int j = 0; j < elem->w; j++)
    {
      if(elem->array[i][j] == '*' &&
          !check_range(map->h, map->w, i + pos.y, j + pos.x) ||
          map->array[i + pos.y][j + pos.x] != '.')
        return false;
    }
  return true;
}

int check_connection(map_elem_t *map, map_elem_t  *elem, pos_t pos, char ch)
{

  for(int i = 0; i < elem->h; i++)
    for(int j = 0; j < elem->w; j++)
      if(elem->array[i][j] != '.')
      {
        if(elem->array[i][j] != '.' && find_symbol(map, j + pos.x, i + pos.y, ch))
            return true;
      }
  return false;
}

pos_t play(req_t *core)
{
  pos_t res;
  int h = core->map.h;
  int w = core->map.w;

  int random = rand() % w + 1;
  
  for(int i = 0; i < h; i++)
    for(int j = 0; j < w; j++)
     {
      for(int q = 0; q <= 3; q++)
       {
          if(q == 0)
          {
            res.x = j+random;
            res.y = i+random;
          }
          else if(q == 1)
          {
            res.x = j-random;
            res.y = i-random;
          }
        /*  else if(q == 2)
            {
              res.x = j-random;
              res.y = i+random;
            }*/
          else if (q == 3)
            {
              res.x = j+random;
              res.y = i-random;
            }
         
         if(check_free_space(&core->map, &core->elem, res) &&
            check_connection(&core->map, &core->elem, res, core->symbol))
        {
          return res;
        }
     }
  }
  for(int i = 0; i < h; i++)
    for(int j = 0; j < w; j++)
    {
      res.x = j;
      res.y = i;
  if(check_free_space(&core->map, &core->elem, res) &&
    check_connection(&core->map, &core->elem, res, core->symbol))
    {
      return res;
   }
 }
}

