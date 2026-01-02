#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reorder_string(char *s1, int *v)
{
     if (s1 == NULL || v == NULL)
          return NULL;

     int n = strlen(s1);

     /* Allocate new string (+1 for '\0') */
     char *s2 = malloc((n + 1) * sizeof(char));
     if (s2 == NULL)
          return NULL;

     /* Iterate over the string */
     for (int i = 0; i < n; i++)
     {
          /* Check bounds */
          if (v[i] < 0 || v[i] >= n)
          {
               fprintf(stderr, "Warning: index out of bounds\n");
               free(s2);
               return NULL;
          }

          s2[v[i]] = s1[i];
     }

     s2[n] = '\0';
     return s2;
}

int main(void)
{
     char s1[] = "abcdefgh";
     int v[] = {7, 4, 3, 0, 1, 2, 5, 6};

     char *s2 = reorder_string(s1, v);
     if (s2 != NULL)
     {
          printf("%s\n", s2);  // prints: defcbgha
          free(s2);
     }

     return 0;
}