#include "filler.h"
#include "my_string.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define REQ (0)
#define ANS (1)


void  timeout_reset(struct timeval *timer)
{
  timer->tv_sec = 1;
  timer->tv_usec = 0;
}

void start_game(filler_t *filler)
{
  struct timeval timeout;

  req_t   *core;
  fd_set  rfds;
  fd_set  wfds;
  pos_t   p;

  FILE  *logg = fopen("filler_proc.log", "w");
  fprintf(logg, "start game\n");
  fclose(logg);

  create_core(core);
  set_nonblocking(0);
  while(42)
  {
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    logg = fopen("filler_proc.log", "a");
    fprintf(logg, "filler status: %d\n", filler->status);
    fclose(logg);

    switch(filler->status)
    {
      case REQ:
        FD_SET(0, &rfds);
        break;
      case ANS:
        FD_SET(1, &wfds);
    }

    timeout_reset(&timeout);

    int ret = select(2, &rfds, &wfds, NULL, &timeout);

    if(ret < 0)
    {}

    if (FD_ISSET(0, &rfds))
    {
      core = read_request(filler);
      if(core != NULL)
      {
        p = play(core);
        filler->status = ANS;
      }
    }

    if (FD_ISSET(1, &wfds))
    {
      print_pos(p);
      filler->status = REQ;
      string_destroy(filler->current_stream);
      filler->current_stream = NULL;
      destroy_core(core);
    }
  }
}

