#include <stdio.h>

int main(int argc, char *argv[])
{
  if(argc == 1)
    printf("Wywołano program.c bez parametrów\n");
  else if(argc == 2)
    printf("Podany parametr dla programu program.c: %s\n", argv[1]);
  else
  {
    printf("Podane parametry dla programu program.c: ");
    for(int i=1; i<argc; i++)
      printf("%s ", argv[i]);
    printf("\n");
  }
  return 0;
}
