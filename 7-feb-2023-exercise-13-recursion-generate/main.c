#include <stdio.h>
#include <stdlib.h>
void recurse(int pos, int n, char *buffer, int sumEven, int sumOdd, FILE *fp);
void generate(char *name,int n);


int main()
{
     int n = 4;
     char *filename = "output.txt";

     printf("Generating %d-digit numbers into %s...\n", n, filename);

     generate(filename, n);

     printf("Done. Check %s for results.\n", filename);

     return 0;
}


void generate(char *name,int n)
{
     if (n <= 0) return;

     FILE *fp = fopen(name, "w");
     if (fp == NULL) {
          fprintf(stderr, "Error opening file %s\n", name);
          exit(EXIT_FAILURE);
     }

     char *buffer = (char *)malloc((n + 1) * sizeof(char)); // n + 1 because of null numerator
     if (buffer == NULL) {
          fprintf(stderr, "Memory allocation failed\n");
          fclose(fp);
          exit(EXIT_FAILURE);
     }
     buffer[n] = '\0';

     // Start recursion from the highest power of 10 (n-1)
     recurse(n - 1, n, buffer, 0, 0, fp);

     free(buffer);
     fclose(fp);
}

void recurse(int pos, int n, char *buffer, int sumEven, int sumOdd, FILE *fp) {

     if (pos < 0) {
          if (sumEven == sumOdd) {
               fprintf(fp, "%s\n", buffer);
          }
          return;
     }

     int isEvenPos = (pos % 2 == 0);
     int start, step;


     if (isEvenPos) {
          start = 0;
          step = 2; // Iterates 0, 2, 4, 6, 8
     } else {
          start = 1;
          step = 2; // Iterates 1, 3, 5, 7, 9
     }


     for (int digit = start; digit <= 9; digit += step) {

          // Leading zero
          if (pos == n - 1 && digit == 0) {
               continue;
          }

          int strIndex = (n - 1) - pos;
          buffer[strIndex] = digit + '0';

          int newSumEven = sumEven + (isEvenPos ? digit : 0);
          int newSumOdd  = sumOdd  + (!isEvenPos ? digit : 0);

          // Recursive call for the next position
          recurse(pos - 1, n, buffer, newSumEven, newSumOdd, fp);
     }
}