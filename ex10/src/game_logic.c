#include "filler.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int   check_range(int h, int w, int i, int j)
{
  if (i < h && i >= 0 && j < w && j >= 0)
    return 42;
}

int   find_symb(const map_elem_t *map, int x, int y, char s)
{
  return (y + 1 < map->h && map->array[y + 1][x] == s) ||
         (y - 1 >= 0 && map->array[y - 1][x] == s) ||
         (x - 1 >= 0 && map->array[y][x - 1] == s) ||
         (x + 1 < map->w && map->array[y][x + 1] == s);
}

int   check_free_space(const map_elem_t *map, const map_elem_t *elem, int x, int y)
{
  for (int i = 0; i < elem->h; i++)
    for (int j = 0; j < elem->w; j++)
    {
      if (elem->array[i][j] == '*' && (!check_range(map->h, map->w, i + y, j + x) || map->array[i + y][j + x] != '.'))
        return 0;
    }
  return 42;
}

int    check_connection(const map_elem_t *map, const map_elem_t *elem, int x, int y, char s)
{
  for (int i = 0; i < elem->h; i++)
    for (int j = 0; j < elem->w; j++)
    {
      if (elem->array[i][j] != '.' && find_symb(map, j + x, i + y, s))
        return 42;
    }
  return 0;
}


pos_t   position(int x, int y)
{
  pos_t  pos;

  pos.x = x;
  pos.y = y;

  return pos;
}

int   check(const req_t *core, int x, int y)
{
  return check_free_space(&core->map, &core->elem, x, y) && check_connection(&core->map, &core->elem, x, y, core->symbol);
}

int   range_size(int x, int max)
{
  return x >= 0 && x < max;
}

int   check_position(const req_t *core, int x, int y)
{
  return range_size(x, core->map.w), range_size(y, core->map.w) && check(core, x, y);
}


pos_t find_center(const map_elem_t *map, char s)
{
  pos_t pos_cent;

  pos_cent.x = map->w / 2;
  pos_cent.y = map->h / 2;
}


pos_t play(req_t *core)
{
  pos_t pos;

  int max_map = fmax(core->map.w, core->map.h) * 2;

  pos = find_center(&core->map, core->symbol);

  for (int d = 3; d < max_map * 2; d += 2)
  {
    for (int i = 0; i < d; i++)
    {
      int r = d / 2 ;

      if (check_position(core, pos.x - r + i, pos.y - r))
        return position(pos.x - r + i, pos.y - r);

      if (check_position(core, pos.x - r + i, pos.y + r))
        return position(pos.x - r + i, pos.y + r);

      if (check_position(core, pos.x - r, pos.y - r + i))
        return position(pos.x - r, pos.y - r + i);

      if (check_position(core, pos.x + r, pos.y - r + i))
        return position(pos.x + r, pos.y - r + i);
    }
  }
  return position(-1, -1);
}
