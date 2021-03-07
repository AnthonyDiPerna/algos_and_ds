#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//-----------------
//1.3 URLify
//-----------------
// Replace " " with "%20"

// T: O(n) S: O(1) - Change string in place, work backwards, assume char array has enough room for the changes

//modifies the string in place, must be a char array not string literal
void urlify_string(char str[])
{
  int len = strlen(str);
  int numSpaces = 0;
  //1 count the number of spaces - this tells the size of the char array we need in total
  //2 work backwards from end expanding the string
  for (int i = 0; i < len; i++)
  {
    if (str[i] == ' ')
    {
      numSpaces++;
    }
  }

  //Check size of char array to make sure this will fit
  int neededLen = len + numSpaces*2; //we are replacing a single character with 3, so increase of 2 chars per space
  str[neededLen] = '\0';             //new end of longer string
  
  //loop backwards through original string
  //if " " then expand to %20
  //otherwise take char directly
  int expandedIndex = neededLen;
  for (int j = len-1; j > 0; j--)
  {
    if (str[j] == ' ')
    {
        str[expandedIndex-1] = '0';
        str[expandedIndex-2] = '2';
        str[expandedIndex-3] = '%';
        expandedIndex -= 3;
    }
    else
    {
      str[expandedIndex - 1] = str[j];
      expandedIndex--;
    }
  }
}

int main() {    
  //array of characters vs string literal  
  char testString[] = "the boy bought the basketball  ";
  
  printf("\nINPUT : test string %s ",testString);
  urlify_string(testString);
  printf("\nRESULT: URLified string %s ",testString);
  
  return 0;
}