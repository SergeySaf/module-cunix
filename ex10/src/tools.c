#include "filler.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "my_string.h"
#include <fcntl.h>
#include <unistd.h>

int       set_nonblocking(int fd)
{
 int flags;

 flags = fcntl(fd, F_GETFL, 0);

 return fcntl(fd, F_SETFL, flags | O_NONBLOCK);

}

void      fatal(char *msg)
{
  int size = strlen(msg);

  if (msg != NULL)
    write(2, msg, size);
  exit(1);
}

void      create_filler(filler_t *filler)
{
   filler->current_stream = NULL;
   filler->status = 0;
   filler->find_enemy = 0;
}


void      destroy_filler(filler_t *filler)
{
   string_destroy(filler->current_stream);
}

void      create_req(req_t *req)
{
  req = (req_t*) malloc(sizeof(req_t));
}

void destroy_req(req_t *req)
{
  for(int i = 0; i < req->map.h; i++)
   free(req->map.array[i]);
  free(req->map.array);

  for(int i = 0; i < req->elem.h; i++)
   free(req->elem.array[i]);
  free(req->elem.array);

  free(req);
  req = NULL;
}
