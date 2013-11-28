

#include <stdio.h>
#include <stdlib.h>
#include "dynqueue.h"


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

void add (char item, queuetype *que)
{  node *p;
   if (! full(*que))
   {  
   p = malloc (sizeof(node));
   p -> info = item;
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
        if (que -> top == NULL)
           que -> bottom = NULL;
        else
        {
           p = que -> top;
           *item = que -> top -> info;
           que -> top = que -> top -> next;
        }
        free (p);
   }
}  




 