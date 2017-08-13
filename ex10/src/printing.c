#include <stdio.h>
#include <stdlib.h>
#include "filler.h"
#include "my_string.h"

void    print_pos(pos_t p)
{
  dprintf(1, "%i %i", p.x, p.y);

  FILE *logg = fopen("filler.log", "a");
  fprintf(logg, "Printed position\n");
  fclose(logg);
}
