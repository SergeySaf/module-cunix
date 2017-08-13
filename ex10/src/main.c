#include "filler.h"
#include "my_string.h"

#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int         main()
{
  filler_t  filler;

  srand(time(NULL));
  create_filler(&filler);
  start_game(&filler);
  destroy_filler(&filler);
  return 0;
}
