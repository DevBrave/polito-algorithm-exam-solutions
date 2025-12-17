// Write the following C function:
// void lcp (char **string, int n);
// To find the Longest Common Prefix among strings. The function receives an array of pointers to strings (string); n
// indicates the number of strings. Each string has a maximum length of 20 characters. The function finds the longest
// common prefix among the strings.
// For example, if the input strings are the following {‘‘flower’’, ‘‘flow’’, ‘‘flight’’}, the function must
// display (on the standard output) ‘‘fl’’.
// Write the entire function using standard C libraries but implement all required personal libraries. Modularize the
// function adequately and report a brief description of the data structure and the logic adopted in plain English. Unclear
// or awkward code, complex or impossible to understand, will be penalized in terms of the final evaluation.


#include <stdio.h>
#include <string.h>


void lcp(char**, int);

int main()
{
     char* string[] = {"flower", "flow", "flight"}; // not modifiable and read-only mode
     int n = 3; // number of words or rows
     lcp(string, n);
     return 0;
}

void lcp(char** string, int n)
{
     char prefix[21];
     if (n == 0)
     {
          printf("\n");
          return;
     }
     // put the first word into prefix to compare each words with the prefix
     strncpy(prefix, string[0], 20);
     prefix[20] = '\0';

     for (int i = 1; i < n; i++)
     {
          int j = 0;
          while (prefix[j] != '\0' && string[i][j] != '\0' && prefix[j] == string[i][j])
          {
               j++;
          }
          prefix[j] = '\0'; // truncate the prefix to the common part
     }
     // output the result
     printf("%s\n", prefix);
}


// Describe the flow
// We could have use three nested loop to check each first second third ... char of each word in the string array
// But we just put the first word into another array to create a pattern and make other word to obey the rules
// This is so much easier than I taught and I made the same mistake again