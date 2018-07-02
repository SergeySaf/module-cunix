#ifndef _FILLER_H_
#define _FILLER_H_


typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  stream_s
{
  char          *str;
  unsigned int  size;
  unsigned int  limit;
} 
              stream_t;

typedef struct  filler_s
{
  char           symbol;
  int            w; //board width
  int            h; //board height
  char         **map; //not freed till the end of the game
  char         **prev_map; //not freed till the end of the game
}               filler_t;

/* My types */
typedef struct  elem_s
{
  int            fig_w;
  int            fig_h;  
  char          **figure;
}               elem_t;



pos_t           play(filler_t *filler, elem_t *elem);

void            print_pos(pos_t p);

void            read_inp(filler_t *filler, elem_t *elem);

filler_t        *create_filler();
void            destroy_filler(filler_t *filler);

elem_t          *create_elem();
void            destroy_elem(elem_t *elem);



#endif // _FILLER_H_
