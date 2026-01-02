// Write the following C function:
// int check_isomorphic_tree (tree_t *rootA, tree_t *rootB);
// That receives the pointer to the root of two binary trees (rootA and rootB) and checks if they are isomorphic. Notice
// that two trees are isomorphic if one can be transformed into the other by swapping some nodes’ left and right children
// (and left untouched the children of all other nodes). The function must return one if the two trees are isomorphic,
// and zero otherwise. The nodes of the tree include dynamic strings. Report the structure of type tree t (that includes
// the two pointers and the dynamic string).
// Hints: Use recursion to check if the structure and values match directly or after swapping the left and the right
// subtrees. Both subtrees must either be isomorphic or identical at each step.
// Write the entire function using standard C libraries, but implement all required personal libraries. Modularize the
// function adequately and report a brief description of the data structure and the logic adopted in plain English. Unclear
// or awkward code, complex or impossible to understand, will be penalized in terms of the final evaluation.


#include <stdio.h>
#include <stdlib.h>



static char** alloc_matrix(int r, int c)
{
     char** mat = malloc((size_t)r * sizeof(*mat));
     if (!mat)
     {
          perror("malloc");
          exit(EXIT_FAILURE);
     }

     for (int i = 0; i < r; i++)
     {
          mat[i] = malloc((size_t)c * sizeof(*mat[i]));
          if (!mat[i])
          {
               perror("malloc");
               exit(EXIT_FAILURE);
          }
     }
     return mat;
}

static void free_matrix(char** mat, int r)
{
     if (!mat) return;
     for (int i = 0; i < r; i++) free(mat[i]);
     free(mat);
}

static void print_matrix(char** mat, int r, int c)
{
     for (int i = 0; i < r; i++)
     {
          for (int j = 0; j < c; j++)
          {
               /* print as integer so you see 0..9 correctly even though stored as char */
               printf("%d ", (unsigned char)mat[i][j]);
          }
          printf("\n");
     }
}

static int row_equal(char** mat, int a, int b, int c)
{
     for (int j = 0; j < c; j++)
     {
          if (mat[a][j] != mat[b][j]) return 0;
     }
     return 1;
}

static int col_equal(char** mat, int a, int b, int r)
{
     for (int i = 0; i < r; i++)
     {
          if (mat[i][a] != mat[i][b]) return 0;
     }
     return 1;
}


char** compress(char** mat, int* r, int* c)
{
     if (!mat || !r || !c || *r <= 0 || *c <= 0) return mat;


     int R = *r;
     int C = *c;

     int write_r = 0;
     for (int read = 0; read < R; read++)
     {
          int duplicate = 0;

          for (int j = 0; j < write_r; j++)
          {
               if (row_equal(mat, read, j, C))
               {
                    duplicate = 1;
                    break;
               }
          }

          if (duplicate == 0)
          {
               if (write_r != read)
               {
                    for (int k = 0; k < C; k++)
                    {
                         mat[write_r][k] = mat[read][k];
                    }
               }

               write_r++;
          }
     }
     R = write_r;

     int write_c = 0;

     for (int read = 0; read < C; read++)
     {
          int duplicate = 0;
          for (int k = 0; k < write_c; k++)
          {
               if (col_equal(mat, read, k, R))
               {
                    duplicate = 1;
                    break;
               }
          }

          if (duplicate == 0)
          {
               if (read != write_c)
               {
                    for (int j = 0; j < R; j++)
                    {
                         mat[j][write_c] = mat[j][read];
                    }
               }
               write_c++;
          }
     }
     C = write_c;

     *r = R;
     *c = C;
     return mat;
}

/* ---------- Example main (uses the matrix from the statement) ---------- */

int main(void)
{
     int r = 5, c = 6;

     char** mat = alloc_matrix(r, c);

     /* Fill matrix with the example values:
        1 2 3 4 5 1
        1 2 3 4 5 1
        6 7 8 9 0 6
        6 7 8 9 0 6
        1 3 5 7 9 1
     */
     unsigned char data[5][6] = {
          {1, 2, 3, 4, 5, 1},
          {1, 2, 3, 4, 5, 1},
          {6, 7, 8, 9, 0, 6},
          {6, 7, 8, 9, 0, 6},
          {1, 3, 5, 7, 9, 1}
     };

     for (int i = 0; i < r; i++)
          for (int j = 0; j < c; j++)
               mat[i][j] = (char)data[i][j];

     printf("Original matrix (%d x %d):\n", r, c);
     print_matrix(mat, r, c);

     mat = compress(mat, &r, &c);

     printf("\nCompressed matrix (%d x %d):\n", r, c);
     print_matrix(mat, r, c);

     free_matrix(mat, r);
     return 0;
}
