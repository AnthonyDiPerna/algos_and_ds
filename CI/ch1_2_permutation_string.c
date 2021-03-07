#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int cmpfunc (const void * a, const void * b) {
  //printf("comparing %c and %c\n", *((char *)a), *((char *)b));
  //printf("compare as char %d - %d = %d\n", *(char *)a, *(char *)b, *(char *)a - *(char *)b);
  // typecast the void pointers to correct type
  return *(char *)a - *(char *)b; 
}
//-----------------
//1.2 String Permutations
//-----------------
// Write a method to determine if a string is a permutation of another
// Definition of Permutation - two words with the same character counts

// T: O(n+m) S: O(1) - Iterate through str1, adding character counts.  Iterate through str2, removing character counts
// If we don't have a character to remove ... then this is not a permutation

// T: O(nlogn * nlogn * n) S: O(1) - Sort each string and compare character by character


//Gotchas:
//ASCII smaller table for supporting data structure, UNICODE much larger 
bool check_permutations_sorted(char str[], char str2[])
{
  printf("\ncheck_permutations_sorted");
  
  int len1 = strlen(str);
  int len2 = strlen(str2);
  
  //Ensure strings need to be same len
  if (len1 != len2)
  {
    return false; 
  }

  //sort each string, then compare
  qsort(str, len1, sizeof(str[0]), cmpfunc);
  qsort(str2, len2, sizeof(str2[0]), cmpfunc);
  
  //compare the strings
  for (int i=0; str[i] != '\0'; i++)
  {
    if (str[i] != str2[i])
    {
      return false;
    }
  }

  return true;
}

//Gotchas:
//ASCII smaller table for supporting data structure, UNICODE much larger 
bool check_permutations_char_count(char str[], char str2[])
{
  int len1 = strlen(str);
  int len2 = strlen(str2);
  
  //Ensure strings need to be same len
  if (len1 != len2)
  {
    return false; 
  }

  int letters[128] = {0}; //Assume ascii, counter for each char in ascii table

  //add character counts
  for (int i = 0; i < len1; i++)
  {
    letters[str[i]]++;
  }

  //remove character counts, any neg numbers means missing char
  for (int j = 0; j < len2; j++)
  {
    if (--letters[str2[j]] < 0)
    {
      return false;
    }
  }

  return true;
}

int main() {    
  //array of characters vs string literal  
  char testString[] = "school";
  char compareString[] = "loohsc";
  
  printf("\nINPUT : %s vs %s",testString,compareString);
  bool result = check_permutations_char_count(testString,compareString);
  printf("\nRESULT: string %s compare %s isPermutation %d",testString,compareString,result);
  
  return 0;
}