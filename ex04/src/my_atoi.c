#include <stdlib.h>
#include <stdio.h>

int my_atoi(char *str)
{
	int i=0, negative=0, numb=0;
  
  while(str[i] == ' ')
	  i++;
  if (str[i] == '-')
		negative = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		numb = numb * 10 + (str[i] - '0');
		i++;
	}
	if (negative == 1)
		return (-numb);
	else
		return (numb);
}

