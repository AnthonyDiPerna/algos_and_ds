#include <stdio.h>
#include <stdlib.h>
#define SIZE (6)

//Recursive binary search

//Search for searchVal, return the value that matches or is higher
int binary_search(int * arr, int searchVal, int l, int r)
{
  static int foundVal = -1;
  
  if (l < r)
  {
    //split when more then 2 elements
    int mid = l + ((r-l)/2);

    //sorted array, less then midpoint means we need to check left side of arr
    if (searchVal <= arr[mid])
    {
        binary_search(arr,searchVal,l,mid);
    } 
    else
    {
        binary_search(arr,searchVal,mid+1,r);
    }
  }
  else
  {
    //1 element left
    foundVal = arr[l];
  }
  
  return foundVal;
}

int main() {     
 	
  //Search sorted array
  int arr[SIZE] = {26,31,41,41,58,59};

  int searchVal = 41;
  printf("\nsearch for %d find %d",searchVal,binary_search(arr,searchVal,0,SIZE));
  searchVal = 42;
  printf("\nsearch for %d find %d",searchVal,binary_search(arr,searchVal,0,SIZE));
  searchVal = 59;
  printf("\nsearch for %d find %d",searchVal,binary_search(arr,searchVal,0,SIZE));
  searchVal = 26;
  printf("\nsearch for %d find %d",searchVal,binary_search(arr,searchVal,0,SIZE));
  searchVal = 90;
  printf("\nsearch for %d find %d",searchVal,binary_search(arr,searchVal,0,SIZE));
  searchVal = 0;
  printf("\nsearch for %d find %d",searchVal,binary_search(arr,searchVal,0,SIZE));
  
  return 0;
}