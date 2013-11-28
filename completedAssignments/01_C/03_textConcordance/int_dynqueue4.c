

#include <stdio.h>
#include <stdlib.h>
#include "int_dynqueue4.h"


int_boolean int_empty (const int_queuetype *int_que)
{  
   return ((int_boolean) (int_que -> top == NULL));
}

int_boolean int_full (const int_queuetype *int_que)
{  
   return int_false;
}

void int_init (int_queuetype *int_que)
{ 
   int_que -> bottom = NULL;
   int_que -> top = NULL; 
}

void int_add (int *int_item, int_queuetype *int_que) /*ADD TO BOTTOM*/
{  
   int_node *p;
   int *n;
  
   p = malloc (sizeof(int_node));
   p -> next = NULL;
   p -> int_info = int_item;
   if (int_empty(int_que))
      int_que -> top = p;
   else
   {  
      int_que -> bottom -> next = p;
   }
   int_que -> bottom = p;

}

int *int_remove (int_queuetype *int_que)   /*REMOVE FROM TOP*/
{  
   int_node *p;
   int *n;
   
   if (! int_empty(int_que))
   {  
      p = int_que -> top;
      int_que -> top = int_que -> top -> next;
      n = p -> int_info;   
      free (p);      
   }
  
   return n;
}  




 