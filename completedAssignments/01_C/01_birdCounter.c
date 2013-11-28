#include <stdio.h>

#define maxelements 15



int greater (int stuff[], int max)
{
  int x, big;
  big = 1;
  for (x = 2; x < max + 1; x++)
  {
     if(stuff[x] > stuff[big])
	big = x;
  }
  return (big);
}

int lesser (int stuff[], int max)
{
  int x, small;
  small = 1;
  for (x = 2; x < max + 1; x++)
  {
     if(stuff[x] < stuff[small])
	small = x;
  }
  return (small);
}
   


int tot (int stuff[], int max)
{
  int sum;
  int x;

  sum = 0;
  for (x = 1; x < max + 1; x++)
  {  sum = sum + stuff[x];
  }
  return (sum);
}


float avg (int stuff[], int max)
{
   int sum;
   int x;

   sum = 0;
   for (x = 1; x < max + 1; x++)
   { sum = sum + stuff[x];
   }
   return (sum / max);
}






main()
{

int bird_array[maxelements];
int x, c, total, most, least;
float average;

	for(x = 1; x < maxelements + 1; x++)
	{
	   printf("How many birds on day ");
	   printf("%d? ", x);
	   scanf("%d", &c);
	   bird_array[x] = c; 
	}


        total = tot(bird_array, maxelements);
        printf("Total number of birds counted: %d\n", total);

	average = avg(bird_array, maxelements);
        printf("Average amount of birds per day: %1.1f\n", average);

        most = greater(bird_array, maxelements);
        printf("The most birds were spotted on day: %d\n", most);

        least = lesser(bird_array, maxelements);
        printf("The least birds were spotted on day: %d\n", least);
        
}

