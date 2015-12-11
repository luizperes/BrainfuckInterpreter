#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
  fpos_t *positionBeginBracket;
  fpos_t *positionEndBracket;
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
  Stack *lastBeginBracket = NULL;
  
  int c = fgetc(f); 
  while(c != EOF)
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
        Stack *auxPtr = lastBeginBracket;
 
        if (*ptr == '\0')
        {
          if (lastBeginBracket == NULL || lastBeginBracket->positionEndBracket == NULL)
          {  
            while(c != ']' && c != EOF)
              c = fgetc(f);
          }
          else
          {
            fsetpos(f, lastBeginBracket->positionEndBracket);
          }

          if (auxPtr != NULL)
          {
            lastBeginBracket = lastBeginBracket->previous;
            free(auxPtr->positionBeginBracket);
            free(auxPtr->positionEndBracket);
            free(auxPtr);
          }
          
          break;
        }
        else if (lastBeginBracket != NULL)
        {
          fpos_t *curBracket = (fpos_t *) malloc(sizeof(fpos_t));
          fgetpos(f, curBracket);
          Stack *searchAuxPtr = lastBeginBracket;
          while(searchAuxPtr != NULL && (*curBracket).__pos != (*searchAuxPtr->positionBeginBracket).__pos)
            searchAuxPtr = searchAuxPtr->previous;
          free(curBracket);
          
          if (searchAuxPtr != NULL)
            break;
        }

        lastBeginBracket = (Stack *) malloc(sizeof(Stack));
        lastBeginBracket->positionBeginBracket = (fpos_t *) malloc(sizeof(fpos_t));
        lastBeginBracket->positionEndBracket = (fpos_t *) malloc(sizeof(fpos_t));
        fgetpos(f, lastBeginBracket->positionBeginBracket);
        lastBeginBracket->previous = auxPtr;
        
        break;
      }
      case ']':
      {
        fgetpos(f, lastBeginBracket->positionEndBracket);
        fsetpos(f, lastBeginBracket->positionBeginBracket);
        c = '[';
        continue;
      }
    }  

    c = fgetc(f);
  }

  fclose(f);
  
  return 0;
}
