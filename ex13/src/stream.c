#include "filler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stream.h"

void stream_print(stream_t* stream)
{
  printf("%s", stream->str);
}

stream_t *stream_init()
{
  stream_t* stream;
  
  stream = (stream_t *) malloc(sizeof(stream_t));
  stream->str = (char*) malloc((BUF_SIZE+1)*sizeof(char));
  stream->str[0] = '\0';
  stream->size = BUF_SIZE;
  stream->limit = 0;
  return stream;
}

void stream_append(stream_t *stream, char *str)
{
  int len;
  
  len = strlen(str);
  if(stream->limit + len > stream->size)
  {
    stream->size = (int)(stream->size * COEF) + len;
	  stream->str = realloc(stream->str, (stream->size + 1) * sizeof(char));
  }
  stream->limit = stream->limit + len;
  strcat(stream->str, str);
}

void stream_destroy(stream_t *stream)
{
  free(stream->str);
  free(stream);
}

