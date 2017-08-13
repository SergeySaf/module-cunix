#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "filler.h"



pos_t       parse_size(char *rez)
{
  int       size;
  char      *part1, *part2;
  pos_t     p;

  size = strlen(rez);

  part1 = malloc(size);

  int i = 0;
  while(rez[i] != ' ')
  {
    part1[i] = rez[i];
    i++;
  }
  part1[i] = '\0';
  i++;

  part2 = malloc(size);
  int j = 0;
  while(rez[i] != '\n')
  {
    part2[j] = rez[i];
    i++;
    j++;
  }
  part2[j] = '\0';

  p.x = atoi(part1);
  p.y = atoi(part2);

  free(part1);
  free(part2);

  return p;
}

int   find_size(char res[32], char *buf, int start_pos)
{
  int i = 0;
  do
  {
    res[i] = buf[start_pos];
    start_pos++;
    i++;
  }
  while (buf[start_pos-1] != '\n');
  res[i] = '\0';
  start_pos++;
  return i-1;
}

void   read_matrix(char** matrix, char* array, int pos, int w, int h)
{
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      matrix[i][j] = array[pos];
      pos++;
    }
    matrix[i][w] ='\0';
    pos++;
  }
}

req_t*   parse_all(char *all)
{
  req_t *temp;
  pos_t size;
  char size_array_map[32] = "\0";
  char size_array_el[32] = "\0";
  int pos = 2;
  int diff;

  FILE  *logg = fopen("filler_proc.log", "a");
  fprintf(logg, "parse start\n");

  temp = NULL;
  temp = (req_t*) malloc (sizeof(req_t));

  temp->symbol = all[0];

  diff = find_size(size_array_map, all, pos);
  pos += diff + 1;

  size = parse_size(size_array_map);
  temp->map.h = size.x;
  temp->map.w = size.y;

  temp->map.array = malloc(temp->map.h * sizeof(char*));
  for (int j = 0; j < temp->map.h; j++)
    temp->map.array[j] = malloc((temp->map.w + 1) * sizeof(char));

  read_matrix(temp->map.array, all, pos, temp->map.w, temp->map.h);
  pos += temp->map.h*(temp->map.w + 1);

  diff = find_size(size_array_el, all, pos);
  pos += diff + 1;

  size = parse_size(size_array_el);
  temp->elem.h = size.x;
  temp->elem.w = size.y;

  temp->elem.array = malloc(temp->elem.h * sizeof(char*));
  for (int i = 0; i < temp->elem.h; i++)
    temp->elem.array[i] = malloc((temp->elem.w + 1) * sizeof(char));

  read_matrix(temp->elem.array, all, pos, temp->elem.w, temp->elem.h);

  fprintf(logg, "parse finished\n");
  fclose(logg);

  return temp;
}

