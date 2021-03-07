#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//-----------------
//1.1 Unique String
//-----------------
// T: O(n^2) S: O(1)  - No data structure, loop through twice
// T: O(n)   S: O(1)  - Direct address helper array, restrict characters we check in string (i.e. 128 in ascii table) 
//                      mark characters as seen/not seen so we don't have to loop twice. 
// T: O(n)   S: O(1)  - assume characters 'a' - 'z', and we can fit the 26 chars in a single int and use
//                      bits to represent the characters (Bitmasks)

//Gotchas:
//ASCII smaller table for supporting data structure, UNICODE much larger 
//Bound the problem deeper in order to optimize



//TIME - O(n^2) loop through the entire set of characters twice
//  - once to start search for each character
//  - once to check search character at all other characters
// SPACE - O(1) no extra data structures added

// Assume all string is null terminated
// Assume a and A are unique (only care character is unique)
// Handles "", and returns true (all characters unique)
// 0 < len < MAX_INT
bool all_unique_in_string(char * str)
{
  for (int i=0; str[i] != '\0'; i++)
  {
    for (int j=i+1; str[j] != '\0'; j++)
    {      
      if (str[i] == str[j])
      {
        return false;
      }
    }
  }

  return true;
}

//Assume letters 'a' to 'z' only, i.e. all fits in 32-bits
bool all_unique_in_string_bit_vector(char * str)
{
  unsigned int check = 0;
  for (int i=0; str[i] != '\0'; i++)
  {
     //good
      int bitValue = str[i] - 'a';
      bool isDupe = (check & (1 << bitValue)) > 0;
      
      if (isDupe)
      {
        return false;
      }

      check |= (1 << bitValue);
  }

  return true;
}

int main() {     
 	
  char * testString = "schouol";
  bool result = all_unique_in_string_bit_vector(testString);

  printf("\nstring %s isUnique %d",testString,result);
  
  return 0;
}