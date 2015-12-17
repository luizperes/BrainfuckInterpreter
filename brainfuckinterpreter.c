#include <stdio.h>
#include <stdlib.h>

#ifdef __llvm__
  #define CHECK_BRACKETS *curBracket != *searchAuxPtr->positionBeginBracket 
#else
  #define CHECK_BRACKETS (*curBracket).__pos != (*searchAuxPtr->positionBeginBracket).__pos
#endif

typedef struct _bf_stack
{
  fpos_t *positionBeginBracket;
  fpos_t *positionEndBracket;
  struct stack *previous;
}Stack;

typedef union _bf_double_byte
{
  short value;
  char charValue;
}bf_double_byte;

int main(int argc, char** argv)
{
  if (argc == 1)
    return -1;
  
  FILE *f = fopen(argv[1], "r");
  if (f == NULL)
    return -1;
  
  bf_double_byte array[30000] = {0};
  bf_double_byte *ptr = array;  
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
        ++((*ptr).value);
        break;
      }
      case '-':
      {
        --((*ptr).value);
        break;
      }
      case '.':
      {
        putchar((*ptr).charValue);
        break;
      }
      case ',':
      {
        (*ptr).charValue = getchar();
        break;
      }
      case '[':
      {
        Stack *auxPtr = lastBeginBracket;
 
        if ((*ptr).value == '\0')
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
            lastBeginBracket = (void *) lastBeginBracket->previous;
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
          while(searchAuxPtr != NULL && CHECK_BRACKETS)
            searchAuxPtr = (void *) searchAuxPtr->previous;
          free(curBracket);
          
          if (searchAuxPtr != NULL)
            break;
        }

        lastBeginBracket = (Stack *) malloc(sizeof(Stack));
        lastBeginBracket->positionBeginBracket = (fpos_t *) malloc(sizeof(fpos_t));
        lastBeginBracket->positionEndBracket = (fpos_t *) malloc(sizeof(fpos_t));
        fgetpos(f, lastBeginBracket->positionBeginBracket);
        lastBeginBracket->previous = (void *) auxPtr;
        
        break;
      }
      case ']':
      {
        fgetpos(f, lastBeginBracket->positionEndBracket);
        fsetpos(f, lastBeginBracket->positionBeginBracket);
        c = '[';
        continue;
      }
      case '#':
      {
        printf("Pointer pos: %lu value: %i\n", (ptr - array), (*ptr).value); 
      }
    }  

    c = fgetc(f);
  }

  fclose(f);
  
  return 0;
}
