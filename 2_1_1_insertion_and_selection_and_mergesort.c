#include <stdio.h>
#include <stdlib.h>
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

//Recursive mergesort
void merge_sort(int * arr, int l, int r)
{
  //printf("\n check left %d right %d",l,r);
    
  if (l < r)
  {
    int mid = l + ((r-l)/2);
    merge_sort(arr,l,mid);
    merge_sort(arr,mid+1,r);
    
    //merge back together
    //copy the halves and combine
    int leftSize = mid-l+1;
    int rightSize = r-mid;
    
    //create temp arrays
    int * left = malloc(sizeof(int) * (leftSize));
    int * right = malloc(sizeof(int) * (rightSize));
    
    //copy data
    for (int z = 0; z < leftSize; z++)
    {
      left[z] = arr[l+z];
    }
    //printf("\n LEFT \n");
    //printArray(left,leftSize);

    for (int z = 0; z < rightSize; z++)
    {
      right[z] = arr[mid+1+z];
    }

    //printf("\n RIGHT \n");
    //printArray(right,rightSize);
    
    //merge!
    int i = 0;
    int j = 0;
    int k = l;

    while (k <= r)
    {
      //right side empty
      if (j >= rightSize)
      {
        arr[k] = left[i++]; 
      }
      //left side empty
      else if (i >= leftSize)
      {
        arr[k] = right[j++]; 
      }
      //left side less then right side
      else if (left[i] < right[j])
      {
        arr[k] = left[i++]; 
      }
      //right side less then left side
      else
      {
        arr[k] = right[j++];
      }
      k++;
    }

    //dont need temp arrays
    free(left);
    free(right);
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

/*
  printf("\nSELECTION SORT\n  ");
  selection_sort(arr,SIZE);
  printArray(arr,SIZE); 
*/
  printf("\nMERGE SORT\n");
  printArray(arr,SIZE); 
  merge_sort(arr,0,SIZE);
  printf("\n");
  printArray(arr,SIZE); 

  return 0;
}