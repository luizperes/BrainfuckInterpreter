#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
  fpos_t *positionFile;
  struct stack *previous;
}Stack;

int main(int argc, char** argv)
{
  if (argc == 1)
    return -1;
  
  FILE *f = fopen(argv[1], "r");
  if (f == NULL)
    return -1;
  
  char array[30000] = {0};
  char *ptr = array;  
  Stack *lastOpenBracket = NULL;
  
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
      case '[':
      {
        if (*ptr == '\0')
        {
          while(c != ']' && c != EOF)
            c = fgetc(f);
          
          if (lastOpenBracket != NULL)
          {
            fpos_t *curBracket = (fpos_t *) malloc(sizeof(fpos_t));
            fgetpos(f, curBracket);
            if (curBracket == lastOpenBracket->positionFile)
            {
              Stack *auxPtr = lastOpenBracket;
              lastOpenBracket = lastOpenBracket->previous;
              free(auxPtr);
            }
          }

          break;
        }

        if (lastOpenBracket == NULL)
        {
          lastOpenBracket = (Stack *) malloc(sizeof(Stack));
          lastOpenBracket->positionFile = (fpos_t *) malloc(sizeof(fpos_t));
          fgetpos(f, lastOpenBracket->positionFile);
          lastOpenBracket->previous = NULL;
        }
        else
        {
          Stack *auxPtr = lastOpenBracket;
          lastOpenBracket = (Stack *) malloc(sizeof(Stack));
          lastOpenBracket->positionFile = (fpos_t *) malloc(sizeof(fpos_t));
          fgetpos(f, lastOpenBracket->positionFile);
          lastOpenBracket->previous = auxPtr;
        }
        
        break;
      }
      case ']':
      {
        fsetpos(f, lastOpenBracket->positionFile);
        ungetc('[', f); 
        break;
      }
    }  
  }

  fclose(f);
  
  return 0;
}
