// Write the following C function:
// void cde (int **mat, int r, int c);
// That counts the number of distinct elements in a matrix. The function receives the matrix (mat) and its size (i.e., r
// rows and c columns) as parameters. It counts the number of distinct elements present in the matrix. For example, if
// the input matrix mat has four rows (r = 4) and three columns (c = 3) and stores the following values:
// 1 2 3
// 4 2 1
// 3 5 6
// 7 3 3
// The function has to display (on standard output) something looking like the following:
// 1[2], 2[2], 3[4], 4[1], 5[1], 6[1], 7[1]
// meaning that the value 1 appears 2 times, the value 2 appears 2 times, the value 3 appears 4 times, etc.
// Write the entire function using standard C libraries but implement all required personal libraries. Modularize the
// function adequately and report a brief description of the data structure and the logic adopted in plain English. Unclear
// or awkward code, complex or impossible to understand, will be penalized in terms of the final evaluation
#include <stdio.h>
#include <stdlib.h>
#define R 4
#define C 3
void cde(int [][C], int, int);
int main () {
     int mat[R][C] = {{1,2,3},{4,2,1},{3,5,6,},{7,3,3}};
     cde(mat, R, C);
     return (1);
}
void cde(int mat[][C], int r, int c)
{
     int i, ii, j, jj, count;
     int **flag;
     flag = malloc (r * sizeof (int *));
     if (flag == NULL) {
          fprintf (stderr, "Allocation error.\n");
          exit (0);
     }
     for (i=0; i<r; i++) {
          // NO need to INIT (calloc)
          flag[i] = calloc (c, sizeof (int));
          if (flag[i] == NULL) {
               fprintf (stderr, "Allocation error.\n");
               exit (0);
          }
     }
     // Traverse the matrix and update counts
     for (i=0; i<r; i++) {
          for (j=0; j<c; j++) {
               if (flag[i][j] == 0) {
                    count = 0;
                    for (ii=i; ii<r; ii++) {
                         for (jj=(ii==i)?j:0; jj<c; jj++) {
                              if (mat[ii][jj]==mat[i][j]) {
                                   flag[ii][jj] = 1;
                                   count ++;
                              }
                         }
                    }
                    fprintf (stdout, "%d[%d] ", mat[i][j], count);
               }
          }
     }
     fprintf (stdout, "\n");
     for (i=0; i<r; i++) {
          free (flag[i]);
     }
     free (flag);
     return;
}