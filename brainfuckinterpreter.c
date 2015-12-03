#include <stdio.h>

int main(int argc, char** argv)
{
  if (argc == 1)
    return -1;
  
  FILE *f = fopen(argv[1], "r");
  if (f == NULL)
    return -1;
  
  char array[30000] = {0};
  char *ptr = array;

  for(int c = fgetc(f); c != EOF; c = fgetc(f))
  {
    switch(c)
    {
      case '>':
      { 
        ++ptr;
        break;
      }
      case '<':
      {
        --ptr;
        break;
      }
      case '+':
      {
        ++*ptr;
        break;
      }
      case '-':
      {
        --*ptr;
        break;
      }
      case '.':
      {
        putchar(*ptr);
        break;
      }
      case ',':
      {
        *ptr = getchar();
        break;
      }
    }  
  }

  fclose(f);
  
  return 0;
}
