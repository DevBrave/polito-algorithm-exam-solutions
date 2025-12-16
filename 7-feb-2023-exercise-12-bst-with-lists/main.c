#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
typedef struct list_s list_t;
typedef struct bst_s bst_t;

struct list_s
{
     char str[N];
     list_t* next;
};

struct bst_s
{
     int key;
     list_t* head;
     bst_t *right, *left;
};


bst_t* bst_insert(char* filename);
bst_t* insert_r(bst_t* root, int key, char* str);
bst_t* new_node(int key, char* str);
list_t* new_list(char* str);
list_t* head_insertion(list_t* head, char* str);
void free_list(list_t *head);
void free_bst(bst_t *root);
void print_bst(bst_t *root);
int main(void)
{
     bst_t* root = bst_insert("input.txt");
     if (!root) return 1;
     print_bst(root);
     free_bst(root);
     return 0;
}

bst_t* bst_insert(char* filename)
{
     char name[N];
     int key;
     bst_t* root = NULL;
     FILE* fp = fopen(filename, "r");
     if (fp == NULL)
     {
          printf("Error raised due to opening a file");
          return NULL;
     }

     while (fscanf(fp, "%d %s", &key, name) == 2)
     {
          // printf("READ: %d %s\n", key, name); // debug
          // insert while searching
          root = insert_r(root, key, name);
     }
     fclose(fp);
     return root;
}

bst_t* insert_r(bst_t* root, int key, char* str)
{
     if (root == NULL)
     {
          return new_node(key, str);
     }
     if (key > root->key)
     {
          // go right
          root->right = insert_r(root->right, key, str);
     }
     else if (key < root->key)
     {
          // go left
          root->left = insert_r(root->left, key, str);
     }
     else
     {
          // a head insertion
          root->head = head_insertion(root->head, str);
          return root;
     }
     return root;
}

bst_t* new_node(int key, char* str)
{
     bst_t* nnode = malloc(sizeof(bst_t));
     if (nnode == NULL)
     {
          return NULL;
     }
     list_t* nlist = new_list(str);
     if (nlist == NULL)
     {
          free(nnode); // <-- REQUIRED
          return NULL;
     }
     // initialize BST node
     nnode->key = key;
     nnode->head = nlist;
     nnode->left = NULL;
     nnode->right = NULL;

     return nnode;
}

list_t* new_list(char* str)
{
     list_t* new_list = malloc(sizeof(list_t));
     if (new_list == NULL)
     {
          return NULL;
     }

     strcpy(new_list->str, str);
     new_list->next = NULL;

     return new_list;
}

list_t* head_insertion(list_t* head, char* str)
{
     list_t* nlist = new_list(str);
     if (nlist == NULL) return head;
     nlist->next = head;
     return nlist;
}


void free_bst(bst_t *root)
{
     if (root == NULL)
          return;

     free_bst(root->left);
     free_bst(root->right);

     //free list
     free_list(root->head);
     free(root);
}

void free_list(list_t *head)
{

     while (head != NULL)
     {
          list_t *temp = head;
          head = head->next;
          free(temp);
     }
}

void print_bst(bst_t *root)
{
     if (root == NULL) return;
     print_bst(root->left);
     printf("Key %d: ", root->key);
     for (list_t *p = root->head; p != NULL; p = p->next)
          printf("%s ", p->str);
     printf("\n");
     print_bst(root->right);
}