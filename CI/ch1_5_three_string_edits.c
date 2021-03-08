#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHARS (128)
//-----------------
//1.5 One Away - Three types of string edits
//-----------------
//Insert character, remove character, replace character
//Given 2 strings write a function  to check if they are one (or zero) edits away from being equal


// T: O(n) S: O(1) - loop through all characters once in a string, no extra data needed

//Figure out if we replace a single character or replace 0 characters
//would the strings be equal
//Required: Strings are the same length (check already handled)
bool oneaway_check_replace_char(char str1[], char str2[], int len)
{
  int num_diffs = 0;
  for (int i = 0; i < len; i++)
  {
    if (str1[i] != str2[i])
    {
      num_diffs++;
      
      if (num_diffs > 1)
        break;
    }
  }

  return num_diffs <= 1;
}

//the smaller char array is always sent in first
//check if we add a single character to the array that we would be ok

//At some point we need to insert, meaning if we find a diff jump the index forward
//i.e. str2=house and str1=hose
//     loop through house
//     we hit a difference at 'u'
//     str1[2] doesn't match, so increase index to jump the missed letter of str2
bool oneaway_check_insert_char(char str1[], int len1, char str2[], int len2)
{
  int index = 0;
  int num_diffs = 0;
  for (int i = 0; i < len2; i++)
  {
    if (str1[index] != str2[i])
    {
        num_diffs++;
        
        if (num_diffs > 1)
          break;

        //Don't update the index of the shorter string here
    }
    else
    {
      //match, increase normally
      index++;
    }
    
  }

  return num_diffs <= 1;
}

bool oneaway_check(char str1[], char str2[])
{
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  bool ret = false;

  //Check for 3 things
  //str1 needs an insert to get to str2 (str1 has one less char) [same as remove from str2]
  //str2 needs an insert to get to str1 (str2 has one less char) [same as remove from str1]
  //str1 needs a letter swap to become str2
  if (len1 < len2 && len2-len1 == 1)
  {
    ret = oneaway_check_insert_char(str1,len1,str2,len2);
  }
  else if (len2 < len1 && len1-len2 == 1)
  {
    ret = oneaway_check_insert_char(str2,len2,str1,len1);
  }
  else if (len2 == len1)
  {
    ret = oneaway_check_replace_char(str1,str2,len1);
  }
  else
  {
    //do nothing
  }

  return ret;
  
}

int main() {    
  char testString[] = "hose"; 
  char compareString[] = "house";
  
  printf("\nINPUT : test string %s compare string %s",testString, compareString);
  printf("\nRESULT: one away check %d ",oneaway_check(testString,compareString));
  
  return 0;
}