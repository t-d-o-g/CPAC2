


#include <stdio.h>
#include <stdlib.h>

#define MAXWORD 80

typedef enum {false, true} boolean;

struct node
{
  char *info;
  struct node *next;
};

typedef struct node node;

struct queuetype 
{
  node *bottom;
  node *top;
};

typedef struct queuetype queuetype;

boolean emp(const queuetype que);

boolean full (const queuetype que);

void init (queuetype *que);

void add (char *item, queuetype *que);

void subtract (char *item, queuetype *que);

 