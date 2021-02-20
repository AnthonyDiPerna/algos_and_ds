#define SIZE (6)

//Sort the array with insertion sort
int arr[SIZE] = {31,41,59,26,41,58};

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

//2.2.2 BIGGEST to SMALLEST
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
 	
   insertion_sort(arr,SIZE);
   
   printf("\nINSERTION SORT");
   
   for (int i = 0; i < SIZE; i++)
   {
     printf("\n   index %d value %d",i,arr[i]);
   }

  insertion_sort_biggest_to_smallest(arr,SIZE);

  printf("\nINSERTION SORT - BIGGEST TO SMALLEST");
   
   for (int i = 0; i < SIZE; i++)
   {
     printf("\n   index %d value %d",i,arr[i]);
   }
   
  return 0;
}