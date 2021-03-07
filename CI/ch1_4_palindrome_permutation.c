#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHARS (128)
//-----------------
//1.4 Palindrome Permutation
//-----------------
// Palindrome - word or phrase that is the same forwards and backwards
// Permutation - rearrangement of letters.  Doesn't have to only be dictionary words

// Need to know how to determine if a set of characters is the same forwards and backwards
//  Even # of characters - we must have an even amount of each character
//  Odd # of characters - even amount of each character AND 1 odd character
//  i.e. can have no matter then 1 character that is odd

// T: O(n) S: O(m) - Create "hash table" for ascii character keys (n len of str, m len of keys)

// Alternates:
//              1 Count odds as we go instead of looping through the "hashtable" at the end, 
//                extra checks per character but save looping time ... tradeoffs
//              2 Use bit vector to save space vs "hashtable"

int getCharNumber (char c)
{
  if (c >= 'a' && c <= 'z')
    return c - 'a';
  else
    return -1;
}


void build_lookup(char str[], int lookup[])
{
  int len = strlen(str);
  //build data structure - direct address 'hash table' where 0 for unused values is OK
  for (int i = 0; i < len; i++)
  {
    int index = getCharNumber(str[i]);
    
    //ignore non a-z character  
    if (index > -1)
    {
      lookup[index]++; 
    }
  }
}
//modifies the string in place, must be a char array not string literal
bool is_palindrome_permutation(char str[])
{ 
  //assume total of 128 different characters (ascii)
  int lookup[MAX_CHARS] = {0};   
  
  //Build direct lookup table for used characters
  build_lookup(str,lookup);

  bool foundOdd = false;
  bool is_palindrome = true;
  
  //Check for at most one odd character
  for (int j = 0; j < MAX_CHARS; j++)
  {
    bool isOdd = (lookup[j] % 2) != 0;
    if (isOdd)
    {
      if (foundOdd)
      {
        is_palindrome = false;
        break;
      }
      else
      {
        foundOdd = true;
      }
      
    }
  }
  return is_palindrome;
}

int main() {    
  char testString[] = "otccata"; //tacocat
  
  printf("\nINPUT : test string %s ",testString);
  printf("\nRESULT: is_palindrome_permutation %d ",is_palindrome_permutation(testString));
  
  return 0;
}