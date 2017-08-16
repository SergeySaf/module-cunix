#include<unistd.h>
#include<stdarg.h>


int my_strlen(char *s)
{
      int i = 0, sum = 0;
      char c = s[0];

      while(c != '\0')
      {
            sum++;
            c = s[++i];
      }
      return sum;
}

int my_pow(int elem, int p) // help in print_integer
{
  if(p == 0) return 1;
  return  elem * my_pow(elem, p-1);
}

int len_int(int a) // count rank
{
    int b = 0;
    while( a > 0)
    {
        a = a / 10;
        b++;
    }
return b;
}

void print_integer(int elem, int padding, char st) //for printf integer
{
  int len = len_int(elem);
  for(int i=0; i < padding - len; i++)
  write(1, &st, 1);
  char st_1;
  for(int i = len; i > 0; i--)
  {
    st_1 = elem / my_pow(10, i-1) + 48;
    write(1, &st_1, 1);
  elem = elem % my_pow(10, i-1);
  }
}


void print_char(char* s, int padding, char st)
{
  int k = 0;
  int len = my_strlen(s);
  for(int i=0; i < padding - len; i++)
  write(1, &st, 1);

  while(s[k] != '\0')
  {
    write(1, &s[k], 1);
    k++;
  }
}


int padding(const char* format, int* posit)
{
  int padd = 0;
  while(format[*posit]>='0' && format[*posit]<='9')
  {
    padd = padd * 10 + (format[*posit]-48);
    ( *posit)++;
  }
  return padd;
}




int my_printf(const char *format, ...)
{
    va_list lst;
    va_start(lst, format);
    int i = 0;

  while(format[i] != '\0')
  {
      if (format[i] == '%')
            switch(format[i+1])
              {
                case 'd':
                  { //int
                    print_integer(va_arg(lst, int), 0, ' ');
                    i += 2;
                    break;
                  }
                case 's':
                  { //char
                    print_char(va_arg(lst, char* ), 0, ' ');
                    i += 2;
                    break;
                  }
                case '%':
                  { //print %
                    write(1, "%", 1);
                    i += 2;
                    break;
                  }
                case '0':
                  { //print padding
                    i++;
                    int padd = padding(format, &i);
                    if(format[i] == 's')
                       print_char(va_arg(lst, char*), padd, '0');
                    else
                       print_integer(va_arg(lst, int), padd, '0');
                    i++;
                    break;
                  }

                default:
                  {
                    i++;
                    int padd = padding(format, &i);
                    if(format[i] == 's')
                       print_char(va_arg(lst, char*), padd, ' ');
                    else
                       print_integer(va_arg(lst, int), padd, ' ');
                    i++;
                    break;
                  }

                }
           else
              {
                write(1, &format[i], 1);
                i++;
              }
   
  }
 va_end(lst);
}


