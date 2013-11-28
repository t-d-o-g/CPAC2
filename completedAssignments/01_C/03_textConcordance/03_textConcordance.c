/* Travis Collins 
 * Text Concordance final draft 3 
 * 3/28/04 
 *
 * My design decisions are based on those discussed in class.
 * 
 * To improve the design, I would replace the queue of integers with
 * a generic queue.  I definitely have a better understanding of pointers and
 * memory allocation which is where I run into most trouble. 
 * 
 *Output files do not include numbers, and count anything separated by 
 *punctuation as a separate word for instance world's is considered two words.
*/      



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "dynqueue4.h"
#include "int_dynqueue4.h"

    

#define MAXWORD 80
#define HASHSIZE 101

struct lnode *lalloc(void);
struct tnode *talloc(void);
void init_occ(struct tnode *);
void add_list(char *, struct tnode *);
void sort_list( struct lnode *);
char valid_char(char);
int strindex(char[], char[]);
unsigned hashfunction(unsigned char *);
char filter(char *, int, queuetype *);
char getword(char *, int);
struct tnode *addtree(char *, struct tnode *, char *, int *);
char tree_traverse(char *, struct tnode *);
struct tnode *tree_search(char *, struct tnode *);
void listprint(struct tnode *, FILE *);
void treeprint(struct tnode *, FILE *, int);
FILE *ifp;
FILE *voc_fp;
FILE *email_fp;
FILE *txt_fp;
FILE *html_fp;


struct lnode
{
   char *file_ref;
   int lcount;
   int_queuetype occ_queue;
   struct lnode *next;
};

typedef struct lnode lnode;
    
struct tnode 
{
   char *word;
   int tcount;
   struct lnode *occ_list;
   struct tnode *left;
   struct tnode *right;
};

static struct tnode *table[HASHSIZE];


                                                         /* ROUTINES */


struct tnode *talloc(void)
{
   return (struct tnode *) malloc(sizeof(struct tnode));
}

struct lnode *lalloc(void)
{
   return (struct lnode *) malloc(sizeof(struct lnode));
}

void init_occ (struct tnode *tn)
{   
   tn -> occ_list -> file_ref = NULL;
   tn -> occ_list -> lcount = 0; 
   tn -> occ_list -> next = NULL;
}

void add_list (char *tf, struct tnode *tn)
{  
   lnode *ln;
   char *t;  
    
   ln = lalloc();
   t = (char *) malloc(strlen(tf) + 1);         
   strcpy(t, tf);    
                        
   ln -> file_ref = t;                  
   ln -> next = tn -> occ_list;         
   tn -> occ_list = ln;
   tn -> occ_list -> lcount = 1;
}

void sort_list( struct lnode *list )
{
    int n;
    char *f;
    struct lnode *head;

    head = list;

    while ( head )
    {
        list = head;

        while ( list )
        {
            if ( head -> lcount < list -> lcount )
            {
                n  = head -> lcount ;
		f = head -> file_ref;
                head -> lcount = list -> lcount;
		head -> file_ref = list -> file_ref;
                list -> lcount = n;
		list -> file_ref = f;
            }

            list = list -> next;
        }

        head  = head -> next;
    }
}                      


char valid_char(char ch)
{  
   int TRUE = 1;
   int FALSE = 0;
   switch(ch)
   {
      case 'a' ... 'z': case 'A' ... 'Z': case '0' ... '9':
      case '@': case '.':  
         return TRUE;
      default:         return FALSE;
      break;
   }
}
 
int strindex(char s[], char t[])
{
   int i, j, k;
   for (i = 0; s[i] != '\0'; i++)
   {
      for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
         ;
      if (k > 0 && t[k] == '\0')
         return i;
   }
   return -1;
}

/* Most simple hash function I could find on the web that 
 * seems to provide good distribution.
 *http://www.dcc.uchile.cl/~rbaeza/handbook/algs/3/331.hash.c
*/

unsigned hashfunction(unsigned char *s)
{
   int m = 100; 
   unsigned i;

   for( i=0; *s; s++ )
   { 
      i = 131*i + *s;
   }

   return( i % m );
}


char filter(char *w, int lim, queuetype *q)
{
   char txt_pattern[] = ".txt";
   char html_pattern[] = ".html";
   char email_pattern[] = "@";
   char indicator;
 
   
   if (strindex(w, txt_pattern) >= 0)
   {
      indicator = 't';
      return indicator;
   }
   else if (strindex(w, html_pattern) >= 0)
   {
      indicator = 'w';
      return indicator;
   }
   else if (strindex(w, email_pattern) >= 0)
   {
      indicator = 'e';
      return indicator;
   }
   else 
   for ( ; --lim > 0; w++)
     if (!isalpha(w[0]))
     {  
        break;
     }
   *w = '\0';
   return w[0];
}

char getword(char *w, int lim)
{
   char c;

   while (isspace(c = getc(ifp)))
      ;
   if (c != EOF)
      *w++ = c;
   if (!isalpha(c))
   {  *w = '\0';
      return c;
   }
   
   for ( ; --lim > 0; w++)
     if (!valid_char(*w = getc(ifp)))   
     {    
        break;
     }
   *w = '\0';
   return w[0];
}


struct tnode *addtree (char *w, struct tnode *tn, char *tf, int *wc)
{
   int cond;
   int *n;

   if (wc != NULL)
   {
      n = (int *) malloc(sizeof(wc));
      *n = *wc;
   }
 
   if (tn == NULL)
   {    
      tn = talloc();
      tn -> word = strdup(w);
      tn -> tcount = 1;
      tn -> left = tn -> right = NULL;
      tn -> occ_list = NULL;
      
      if (tf != NULL)
      {   
         tn -> occ_list = lalloc();       
         init_occ(tn);
         add_list(tf, tn);
         int_add(n, &tn -> occ_list -> occ_queue);
      }
   } 
   else if ((cond = strcmp (w, tn -> word)) == 0)
   {  
      tn -> tcount++;

      if (tf != NULL)
      {
         if ((cond = strcmp (tf, tn-> occ_list -> file_ref)) == 0)   
         {  
            tn -> occ_list -> lcount++;
            int_add(n, &tn -> occ_list -> occ_queue);
         }         
         else
         {   
            add_list(tf, tn);
            int_add(n, &tn -> occ_list -> occ_queue);            
         }   
      }     
   }
   else if (cond < 0)
      tn -> left = addtree (w, tn -> left, tf, wc);
   else
      tn -> right = addtree (w, tn -> right, tf, wc);
   return tn;
}

char tree_traverse(char *w, struct tnode *scan)
{
   int cond;
   int TRUE = 1;
   int FALSE = 0;

   if (scan != NULL)
   { 
      if ((cond = strcmp (w, scan -> word)) < 0)
      { 
        return tree_traverse(w, scan -> left);
      }
      else if ((cond = strcmp (w, scan -> word)) > 0) 
      {
        return tree_traverse(w, scan -> right);
      }  
      else if ((cond = strcmp (w, scan->word)) == 0)
      {
         return TRUE;
      }
   } 
   return FALSE;
}

struct tnode *tree_search(char *w, struct tnode *scan)
{

   if (scan != NULL)
   { 
      if ((strcmp (w, scan -> word)) < 0)
      { 
        return tree_search(w, scan -> left);
      }
      else if ((strcmp (w, scan -> word)) > 0) 
      {
        return tree_search(w, scan -> right);
      }  
      else if ((strcmp (w, scan->word)) == 0)
      {
         return scan;
      }
   } 
   scan = NULL;
   return scan;
}

void listprint(struct tnode *tn, FILE *fp)
{  
   int *wc;

   while (tn -> occ_list -> next != NULL)
   {
      fprintf(fp, "%s\n", tn -> occ_list -> file_ref);
      fprintf(fp, "Total times found in this file: ");
      fprintf(fp, "%d\n", tn -> occ_list -> lcount);
      while (!int_empty(&tn -> occ_list -> occ_queue))
      {
        fprintf(fp, "Occurrence: ");
        wc = int_remove(&tn -> occ_list -> occ_queue);
        fprintf(fp, "%d\n", *wc);
        free(wc);  
      }
      tn -> occ_list = tn -> occ_list -> next;
   }   
}

void treeprint(struct tnode *tn, FILE *fp, int b)
{
   if (tn != NULL) 
   { 
      treeprint (tn -> left, fp, b);
      fprintf(fp, "\n%s\n", tn -> word);
      if (b != NULL)
      {
         listprint(tn, fp);
      }
      treeprint (tn -> right, fp, b);
   }     
}

main(int argc, char *argv[])             /* MAIN */
{   
    struct tnode *voc_root = NULL;        /* DECLARATIONS */
    struct tnode *email_root = NULL;
    struct tnode *web_root = NULL;
    struct tnode *list_ptr = NULL;
    struct tnode *temp_var = NULL;
    char *path;
    char *temp_word;
    queuetype queue;
    char choice;
    char word[MAXWORD];
    char txt_file[MAXWORD];
    char word_type;
    int *word_count;
    int table_loc; 
    int x;  
    int y;
    email_fp=fopen("emails.txt", "w");
    html_fp=fopen("webfiles.txt", "w");
    txt_fp =fopen("textfiles.txt", "w");
    voc_fp=fopen("vocabulary.txt", "w"); 
    
  
    init(&queue);                         /* INITIALIZATIONS */
    
    for(x = 0; x < HASHSIZE; x++)
    {
       table[x] = NULL;
    }

    if (argc == 1)
    {
       printf("  Enter the path and name of a seed file as separate arguments.");
       return 1;
    }

    else if (argc == 2)
    {
       printf("  Enter the path and name of a seed file as separate arguments.");
       return 1;
    }
    else 
    {
       for(x = 2; x < argc; x++)             /* GET INPUT FILE NAMES */
       {      
          path = (char *) malloc(strlen(argv[1]) + strlen(argv[x]));
          strcpy(path, argv[1]); 
          strcat(path, argv[x]);          
          add(path, &queue);
          table_loc = hashfunction(path);
          table[table_loc] = addtree(path, table[table_loc], NULL, NULL);
       }
    }
    
    
    printf("  Text files analyzed.\n\n"); 
    while (!emp(queue))                           /* .TXT_QUEUE RETRIEVAL */
    {  y = 0;
       word_count = &y;
       subtract(txt_file, &queue);           
       ifp=fopen(txt_file, "r");  
       if (!ifp)
       {
          printf("  %s ", txt_file);
          printf("does not exist.\n");
       }
       else
       {      
          printf("  %s\n", txt_file);
          while (getword(word, MAXWORD) != EOF)    /* WORD EXTRACTION */
          {  
            word_type = filter(word, MAXWORD, &queue); 
            if (word_type == 't')
             { 
                (*word_count)++;
                temp_word = (char *) malloc(strlen(argv[1]) + strlen(word));
                strcpy(temp_word, argv[1]);
                strcat(temp_word, word);
                table_loc = hashfunction(temp_word);
                if (!tree_traverse(temp_word, table[table_loc])) 
                {   
                   table[table_loc] = addtree(temp_word, table[table_loc], NULL, word_count);      
                   add(temp_word, &queue);               
                }
             }
             else if (word_type == 'w')
             { 
                (*word_count)++;
                web_root = addtree(word, web_root, NULL, word_count);
             }
             else if (word_type == 'e')
             {
                (*word_count)++;
                email_root = addtree(word, email_root, NULL, word_count);
             }
             else if (isalpha(word[0])) 
             {   
                (*word_count)++;                        
                voc_root = addtree(word, voc_root, txt_file, word_count);                                                           
             }  
          }  
          fclose(ifp);
       }      
    } 

    do
    {  
    printf("\n  1)  Perform a search\n");              /* MENU OPTIONS */
    printf("  2)  Quit\n\n");
    printf("  Enter a choice: ");
    fflush(stdin);
    choice = getchar();
    if (choice == '1')					/* SEARCH */
    {  
       temp_var = talloc();
       *temp_var = *voc_root;
       printf("\n  Enter a key word: ");
       scanf("%s", word);
       if (tree_search(word, temp_var) != NULL)
       {
           
          *temp_var = *tree_search(word, temp_var);
          sort_list(temp_var -> occ_list);
  
          printf("\n  List of files in which the word occurred: \n");
          while (temp_var -> occ_list -> next != NULL)
          {  
             printf("  %s\n", temp_var -> occ_list  -> file_ref);
             printf("  Total times found in this file: ");
             printf("%d\n", temp_var -> occ_list -> lcount);
             temp_var -> occ_list = temp_var -> occ_list -> next;
          }
          free(temp_var);
       }
       else
       {
          printf("  No files contain that word.\n");
       }
    }
    else if (choice == '2')				/* QUIT - PRINT FILES */
    {
       treeprint(email_root, email_fp, NULL);
       treeprint(web_root, html_fp, NULL);                 
       treeprint(voc_root, voc_fp, 1); 
       for (x = 1; x < 101; x++)
       {
          if (table[x] != NULL);
          {
             treeprint(table[x], txt_fp, NULL);
          }
       }
       printf("\n  The words have been printed to separate files. \n");
    }
    } while (choice != '2');
    
    fclose(email_fp);
    fclose(html_fp);
    fclose(txt_fp);
    fclose(voc_fp);
    return 0;
}

