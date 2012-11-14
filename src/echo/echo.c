/* 
>Copyright
>2012
Shiggerino

Insert license information here at some point 
*/

/* 
Usage: echo [-n] [string ...] 
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int
main (int argc, char *argv[])
{

  if (argc < 2)
    {
      return 0;
    }

  bool newline = true;

  if (!strcmp(argv[1], "-n"))
    {
      newline = false;
    }

  for (int i = newline ? 1 : 2; i < argc; i++)
    {
      {
	printf("%s ", argv[i]);
      }
    }

  if (newline)
    {
      printf("\n");
    }

  return 0;
}
