

#include <stdio.h>
#include <stdlib.h>
#include "dynqueue4.h"


boolean emp (const queuetype que)
{  return ((boolean) (que.top == NULL));
}

boolean full (const queuetype que)
{  return false;
}

void init (queuetype *que)
{ 
   que -> bottom = NULL;
   que -> top = NULL; 
}

void add (char *item, queuetype *que)
{  node *p;
   char *n;
   if (! full(*que))
   {  
      p = malloc (sizeof(node));
      n = (char *) malloc(strlen(item) + 1);
      strcpy(n, item);
      p -> info = n;
      p -> next = NULL;
      if (que -> top == NULL)
         que -> top = p;
      else
      {  
         que -> bottom -> next = p;
      }
   que -> bottom = p;
   }
}

void subtract (char *item, queuetype *que)
{  node *p;
   if (! emp(*que))
   {  
      strcpy(item, que -> top -> info);
      p = que -> top;
      que -> top = que -> top -> next;   
      if (que -> top == NULL)
      {
           que -> bottom = NULL;
      }
    free (p);
   }
}  




 