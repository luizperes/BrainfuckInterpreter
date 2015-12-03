#include <stdio.h>

int main(int argc, char** argv)
{
  if (argc == 1)
    return -1;
  
  FILE *f = fopen(argv[1], "r");
  if (f == NULL)
    return -1;

  printf("u");

  return 0;
}
