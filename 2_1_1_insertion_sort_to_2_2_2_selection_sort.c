#include <stdio.h>
#define SIZE (6)


void printArray(int arr[], int size) 
{ 
    for (int i = 0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 

void insertion_sort(int * arr, int len)
{
  for (int i = 1; i <= SIZE-1; i++)
  {
    int j = i;
    //If current index arr[i] < prev index arr[i-1] swap position
    while (j > 0 && arr[j] < arr[j-1])
    {
      //swap this value back a spot
      int tmp = arr[j-1];
      arr[j-1] = arr[j];
      arr[j] = tmp;
      j--;
    }
  }  
}

//2.2.2 BIGGEST to SMALLEST (swap < to > on the swap compare)
void insertion_sort_biggest_to_smallest(int * arr, int len)
{
    for (int i = 1; i <= SIZE-1; i++)
  {
    int j = i;
    //If current index arr[i] > prev index arr[i-1] swap position
    while (j > 0 && arr[j] > arr[j-1])
    {
      //swap this value back a spot
      int tmp = arr[j-1];
      arr[j-1] = arr[j];
      arr[j] = tmp;
      j--;
    }
  }  
}

void selection_sort(int * arr, int len)
{
  for (int i = 0; i <= SIZE-1; i++)
  {
    //i is the index for where we will put a value
    //j is start index for searching for smallest value
    
    int min_index = i;
    for (int j = i+1; j < SIZE; j++)
    {
      //check all values - find the min value and store swap index ... repeat  
      if (arr[j] < arr[min_index])
      {
        min_index = j;
      }
    }

    //find a new min to swap?
    if (min_index != i)
    {
      //swap this value back a spot
      int tmp = arr[i];
      arr[i] = arr[min_index];
      arr[min_index] = tmp;
    }
  }  
}

//output
//INSERTION SORT
//   index 0 value 26
//   index 1 value 31
//   index 2 value 41
//   index 3 value 41
//   index 4 value 58
//   index 5 value 59

/*
INSERTION SORT - BIGGEST TO SMALLEST
   index 0 value 59
   index 1 value 58
   index 2 value 41
   index 3 value 41
   index 4 value 31
   index 5 value 26
*/
int main() {     
 	
  //Sort the array with insertion sort
  int arr[SIZE] = {31,41,59,26,41,58};

  /*
  insertion_sort(arr,SIZE);

  printf("\nINSERTION SORT");

  for (int i = 0; i < SIZE; i++)
  {
    printf("\n   index %d value %d",i,arr[i]);
  }
  */

 /*
  insertion_sort_biggest_to_smallest(arr,SIZE);

  printf("\nINSERTION SORT - BIGGEST TO SMALLEST");

  for (int i = 0; i < SIZE; i++)
  {
    printf("\n   index %d value %d",i,arr[i]);
  }

  insertion_sort_biggest_to_smallest(arr,SIZE);
  */

  printf("\nSELECTION SORT\n  ");
  selection_sort(arr,SIZE);
  printArray(arr,SIZE); 
  return 0;
}