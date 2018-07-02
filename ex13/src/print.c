#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filler.h"
#include "stream.h"

void print_pos(pos_t p)
{
  dprintf(1, "%d %d\n", p.x, p.y);
}
 
