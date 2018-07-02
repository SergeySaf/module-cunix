#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filler.h"
#include "stream.h"

int main()
{
  filler_t *filler;
  elem_t *elem;
  pos_t pos;
  
  filler = create_filler();
  while(1)
  {
    elem = create_elem();
    read_inp(filler, elem);
    pos = play(filler, elem); 
    print_pos(pos);
    destroy_elem(elem);
    elem = NULL;
  }
  destroy_filler(filler);
}

