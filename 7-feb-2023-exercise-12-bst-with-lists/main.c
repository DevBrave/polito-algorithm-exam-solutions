// Exercise 12 (5.0 points)
// A file includes an undefined number of rows. On each row the first field is a string (of maximum of 100 characters),
// and the second an integer value that indicates the number of integer values following it on the same file line. For
// example, the following is a correct file with this format:
// clara 2 28 27
// alfonso 3 19 23 26
// maria 1 15
// clara 3 30 27 28
// raffaela 2 24 25
// alfonso 2 12 19
// Write the function:
// bst_t *file_to_bst_of_lists (char *name);
// which receives the file name as a parameter and returns the pointer to a BST in which each node points to the list
// of integer values associated with the string. The rules for storing the file into a BST of lists are as follows. The BST
// has the strings as keys (and keys are not duplicated). If a string appears more than once in the file (e.g., alfonso,
// in the previous example), the corresponding numbers must be concatenated in the same secondary list. All secondary
// lists store the values associated with the corresponding strings. Those values may appear in any order and can be
// duplicated.
// The following picture represents an example of the BST of lists corresponding to the previos file.
// Thus, for example, the list related to the BST node with key alfonso must include the value 19,23,26,12,19 in any
// order. Define the type bst
// t and list
// allocated.
// t for the BST and the list. The string within the BST must be dynamicall

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 101   /* max 100 chars + '\0' */

/* forward typedefs */
typedef struct list_s list_t;
typedef struct bst_s  bst_t;

/* ---------- list node: stores ONE integer ---------- */
struct list_s {
    int value;
    list_t *next;
};

/* ---------- bst node: key string -> list head ---------- */
struct bst_s {
    char key[N];      /* you can keep it fixed-size like your style */
    list_t *head;     /* list of integers */
    bst_t *left;
    bst_t *right;
};

/* prototypes */
bst_t  *file_to_bst_of_lists(char *filename);
bst_t  *insert_r(bst_t *root, const char *key, int *vals, int k);
bst_t  *new_node(const char *key, int *vals, int k);

list_t *new_list_node(int x);
list_t *head_insertion(list_t *head, int x);

void    free_list(list_t *head);
void    free_bst(bst_t *root);
void    print_bst(bst_t *root);

/* ------------------- main (test) ------------------- */
int main(void)
{
    bst_t *root = file_to_bst_of_lists("input.txt");
    if (!root) return 1;

    print_bst(root);
    free_bst(root);
    return 0;
}

/* ------------------- file reading ------------------- */
bst_t *file_to_bst_of_lists(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file\n");
        return NULL;
    }

    bst_t *root = NULL;
    char name[N];
    int k;

    while (fscanf(fp, "%100s %d", name, &k) == 2) {

        if (k < 0) { /* invalid */
            fclose(fp);
            return root;
        }
        int *vals = NULL;
        if (k > 0) {
            vals = malloc((size_t)k * sizeof(int));
            if (!vals) { fclose(fp); return root; }

            for (int i = 0; i < k; i++) {
                if (fscanf(fp, "%d", &vals[i]) != 1) {
                    free(vals);
                    fclose(fp);
                    return root;
                }
            }
        }
        root = insert_r(root, name, vals, k);

        free(vals);
    }

    fclose(fp);
    return root;
}

/* ------------------- BST insert (return-style) ------------------- */
bst_t *insert_r(bst_t *root, const char *key, int *vals, int k)
{
    if (root == NULL) {
        return new_node(key, vals, k);
    }

    int cmp = strcmp(key, root->key);

    if (cmp < 0) {
        root->left = insert_r(root->left, key, vals, k);   /* FIXED left attach */
    } else if (cmp > 0) {
        root->right = insert_r(root->right, key, vals, k); /* FIXED right attach */
    } else {
        /* same key: concatenate numbers into the existing list */
        for (int i = 0; i < k; i++) {
            root->head = head_insertion(root->head, vals[i]);
        }
        return root;
    }

    return root;
}

bst_t *new_node(const char *key, int *vals, int k)
{
    bst_t *nnode = malloc(sizeof(bst_t));
    if (!nnode) return NULL;

    strcpy(nnode->key, key);
    nnode->left = NULL;
    nnode->right = NULL;
    nnode->head = NULL;

    /* add the k values (order not required, head insertion is OK) */
    for (int i = 0; i < k; i++) {
        nnode->head = head_insertion(nnode->head, vals[i]);
    }

    return nnode;
}

/* ------------------- list helpers ------------------- */
list_t *new_list_node(int x)
{
    list_t *n = malloc(sizeof(list_t));
    if (!n) return NULL;
    n->value = x;
    n->next = NULL;
    return n;
}

list_t *head_insertion(list_t *head, int x)
{
    list_t *n = new_list_node(x);
    if (!n) return head;  /* keep old head if allocation fails */
    n->next = head;
    return n;
}

/* ------------------- free + print ------------------- */
void free_list(list_t *head)
{
    while (head != NULL) {
        list_t *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void free_bst(bst_t *root)
{
    if (!root) return;

    free_bst(root->left);
    free_bst(root->right);

    free_list(root->head);
    free(root);
}

void print_bst(bst_t *root)
{
    if (!root) return;

    print_bst(root->left);

    printf("%s: ", root->key);
    for (list_t *p = root->head; p != NULL; p = p->next) {
        printf("%d ", p->value);
    }
    printf("\n");

    print_bst(root->right);
}
