#include <stdlib.h>
#include <stdio.h>

int poww(int n, int k)
{
  if(k == 0) return 1;
  return n * poww(n, k-1);
}

int str_len(char* s)
{
  int a = 0;
  while(s[a] >= '0' && s[a] <= '9')
    a++;
  return a;
}

int my_rec_atoi(char *str)
{
  char* ptr = str;
  char* next = ++str;
  if( *ptr == '-')
    return -my_rec_atoi(next);
  int len = str_len(ptr);
  if(len == 0)
    return 0;
  if(*next < '0' || *next > '9')
    return (*ptr - '0');
  return (*ptr - '0')*poww(10, len - 1) + my_rec_atoi(next);
}