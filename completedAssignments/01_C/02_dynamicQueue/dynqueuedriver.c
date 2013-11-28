/* Travis Collins "Dynamic Queue" 2/12/04 */


#include <stdio.h>
#include <stdlib.h>
#include "dynqueue.h"


main()
{
  queuetype 	queue;
  char		choice;
  char		item;

  init(&queue);

  do
  {
  printf("\n");
  printf("  1)  Add an item \n");
  printf("  2)  Remove an item \n");
  printf("  3)  Test to see if the queue is full \n");
  printf("  4)  Test to see if the queue is empty \n");
  printf("  5)  Quit \n\n");
  printf("  Enter a choice: ");
  fflush(stdin);
  choice = getchar();

  if (choice == '1')
  {  if (! full(queue))
     {  printf ("  Enter a character: ");
        fflush(stdin);
        item = getchar();
        add( item, &queue);
      }
      else printf ("  The queue is full. \n\n");
  }

  else if (choice == '2')
  {  if (! emp(queue))
     { subtract(&item, &queue);
       printf("  %c \n\n", item);
     }
     else printf ("  The queue is empty. \n\n");
  }
  
  else if (choice == '3')
  {  if (full(queue))
     { printf("  The queue is full. \n\n");
     }
     else printf ("  The queue is not full. \n\n");
  }

  else if (choice == '4')
  {  if (emp(queue))
     {  printf("  The queue is empty. \n\n");
     }
     else printf("  The queue is not empty. \n\n");
  }

  } while (choice != '5');
}