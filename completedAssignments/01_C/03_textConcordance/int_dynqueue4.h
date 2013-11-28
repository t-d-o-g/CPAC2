


#include <stdio.h>
#include <stdlib.h>


typedef enum {int_false, int_true} int_boolean;

struct int_node
{
  int *int_info;
  struct int_node *next;
};

typedef struct int_node int_node;

struct int_queuetype 
{
  int_node *bottom;
  int_node *top;
};

typedef struct int_queuetype int_queuetype;

int_boolean int_empty (const int_queuetype *int_que);

int_boolean int_full (const int_queuetype *int_que);

void int_init (int_queuetype *int_que);

void int_add (int *int_item, int_queuetype *int_que);

int *int_remove (int_queuetype *int_que);

 