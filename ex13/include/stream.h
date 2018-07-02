#ifndef _STREAM_H_
#define _STREAM_H_
#include "filler.h"

#define BUF_SIZE 64
#define COEF 1.5
stream_t        *stream_init();
void            stream_append(stream_t *stream, char* str);
void            stream_print(stream_t* stream);
void            stream_destroy(stream_t *stream);
#endif
