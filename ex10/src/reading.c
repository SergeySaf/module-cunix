#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include "filler.h"
#include "my_string.h"

#define BUF_SIZE 64


int         read_is_finished(stream_t* buf)
{
  int pos = 0;
  bool first_size = true;
  int elem_pos = 0;
  char arr_elem_size[32];
  pos_t el_size;

  while(pos <= buf->size)
  {
    if(buf->str[pos] > '9' || buf->str[pos] < '0')
      pos++;
    else if (first_size)
    {
      while(pos <= buf->size && buf->str[pos] != '\n')
        pos++;
      pos++;
      first_size = false;
    }
    else
    {
      elem_pos = pos;
      while(pos <= buf->size && buf->str[pos] != '\n')
        pos++;
      if(buf->str[pos] != '\n')
        return -1;
      else
      {
        find_size(arr_elem_size, buf->str, elem_pos);
        el_size = parse_size(arr_elem_size);
        FILE *logg = fopen("filler_read.log", "a");
        fprintf(logg, "read_is_finished: pos = %d elem = %d %d buf_size =%d\n", pos,el_size.x,el_size.y, buf->size);
        fclose(logg);
        if(buf->size <= pos + el_size.x*(el_size.y + 1))
          return -1;
        else return 0;
      }
    }
  }
  return -1;
}

void            read_input(filler_t* filler)
{
  char      buffer[BUF_SIZE];
  int       res;

  FILE *logg = fopen("filler_read.log", "a");
  fprintf(logg, "reading\n");
  fclose(logg);

  while(42)
  {
      memset(buffer, 0, BUF_SIZE);
      res = read(0, buffer, BUF_SIZE - 1);
      /*logg = fopen("filler_read.log", "a");
      fprintf(logg,"buffer: %s\n", buffer);
      fclose(logg);*/

      if (res < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
          logg = fopen("filler_read.log", "a");
          fprintf(logg, "GOT errno = EAGAIN#\n");
          fclose(logg);
          break;
        } else {
          fatal("Error while reading(0)");
        }
      }
      if(filler->current_stream == NULL)
      {
        filler->current_stream = string_create(buffer);
      }
      else
        string_append(filler->current_stream, buffer);
  }
  logg = fopen("filler_read.log", "a");
  fprintf(logg,"all buffer: %s\n", filler->current_stream->str);
  fclose(logg);
}

req_t       *read_request(filler_t *filler)
{
  req_t     *req = NULL;

  read_input(filler);

  if(read_is_finished(filler->current_stream) == 0)
    req = parse_all(filler->current_stream->str);

  return req;
}
