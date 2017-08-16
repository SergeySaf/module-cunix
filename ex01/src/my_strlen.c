#include <stdio.h>


int my_strlen(char *str) {
      int i = 0, sum = 0;
      char c = str[0];

      while(c != '\0') {
            sum++;
            c = str[++i];
      }
      return sum;
}


