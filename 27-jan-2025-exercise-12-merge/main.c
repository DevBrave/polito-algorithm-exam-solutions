// listB_t *merge (listA_t *head);
// That receives a list of lists and returns a simple linked list. The main list (pointed by head) contains elements of type
// listA
// t element contains a pointer to a secondary list of elements of type listB
// element stores a string and a pointer to another listB
// t. Each listB
// t
// t element. All secondary lists are sorted alphabetically.
// The function must merge all secondary (already) sorted linked lists into one single (unique) sorted linked list and
// return its pointer (of type listB
// t).
// Define the type listA
// t and listB
// t to implement the linked list with all necessary structure fields.
// Write the entire function using standard C libraries but implement all required personal libraries. Modularize the
// function adequately and report a brief description of the data structure and the logic adopted in plain English. Unclear
// or awkward code, complex or impossible to understand, will be penalized in terms of the final evaluation.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_A_LIST 10
#define NUM_B_LIST 3
typedef struct listB_t list_b;
typedef struct listA_t list_a;

struct listA_t
{
     list_b* b_head;
     list_a* next;
};

struct listB_t
{
     char* string;
     list_b* next;
};

list_a* newA(void);
list_b* newB(char* str);
list_b* merge(list_a* head);
void print_all_b(list_b* head);
list_b* sort_b_list(list_b* head);
void sorted_insert(list_b** sorted, list_b* node);
list_b* remove_duplicates(list_b* head);
void free_b(list_b *head);
void free_a(list_a *head);
int main(void)
{
     // initialize
     list_a* headA = NULL;
     // B list for A1: apple -> banana
     list_b* b1 = newB("apple");
     b1->next = newB("banana");

     // B list for A2: apricot -> cherry
     list_b* b2 = newB("cherry");
     b2->next = newB("cherry");

     // B list for A3: banana -> date
     list_b* b3 = newB("banana");
     b3->next = newB("date");

     list_a* a1 = newA();
     list_a* a2 = newA();
     list_a* a3 = newA();

     a1->b_head = b1;
     a2->b_head = b2;
     a3->b_head = b3;

     // link A nodes
     a1->next = a2;
     a2->next = a3;

     // head of main list
     headA = a1;
     printf("Sorted list\n");
     // sort the list
     list_b *last_b = merge(headA);
     print_all_b(last_b);

     // let's free them all

     free_b(last_b);
     free_a(headA);
}

list_b* newB(char* str)
{
     list_b* b = malloc(sizeof(list_b));
     if (b == NULL)
     {
          printf("Allocation is leaked");
          exit(EXIT_FAILURE);
     }
     b->string = strdup(str);
     b->next = NULL;

     return b;
}

list_a* newA(void)
{
     list_a* a = malloc(sizeof(list_a));
     if (a == NULL)
     {
          printf("Allocation is leaked");
          exit(EXIT_FAILURE);
     }
     a->next = NULL;
     a->b_head = NULL;

     return a;
}


list_b* merge(list_a* head)
{
     // change the last *next address of 'b' node in each 'a' node is the head of next b_head of node 'a'
     list_a* firstA = head;
     list_b* sorted;
     // extract
     while (head != NULL && head->next != NULL)
     {
          list_b* currB = head->b_head;

          if (currB == NULL)
          {
               head = head->next;
               continue;
          }

          // find last B node
          while (currB->next != NULL)
          {
               currB = currB->next;
          }

          // attach to next A's B list
          currB->next = head->next->b_head;

          head = head->next;
     }

     list_b *sorted_list = sort_b_list(firstA->b_head);
     return remove_duplicates(sorted_list);

}


void print_all_b(list_b* head)
{
     int i = 0;
     while (head != NULL)
     {
          printf("B%d = %s\n", i, head->string);
          head = head->next;
          i++;
     }
}

list_b* sort_b_list(list_b* head)
{
     list_b* sorted = NULL;

     while (head != NULL)
     {
          list_b* next = head->next; // save next node
          head->next = NULL; // detach current node

          sorted_insert(&sorted, head);

          head = next;
     }

     return sorted;
}

void sorted_insert(list_b** sorted, list_b* node)
{
     // insert at head
     if (*sorted == NULL ||
          strcmp(node->string, (*sorted)->string) <= 0)
     {
          node->next = *sorted;
          *sorted = node;
          return;
     }

     // walk list to find position
     list_b* curr = *sorted;
     while (curr->next != NULL &&
          strcmp(node->string, curr->next->string) > 0)
     {
          curr = curr->next;
     }

     node->next = curr->next;
     curr->next = node;
}

list_b* remove_duplicates(list_b* head)
{
     list_b* curr = head;
     while (curr != NULL && curr->next != NULL)
          if (strcmp(curr->string, curr->next->string) == 0)
          {
               list_b* dup = curr->next;
               curr->next = dup->next;

               free(dup->string); // strdup() memory
               free(dup); // node
          }
          else
          {
               curr = curr->next;
          }

     return head; // because we will never delete the head and we just free the pointer of duplicated nodes between head and tail
}


void free_a(list_a *head)
{
     // because we still have multiple B nodes in multiple A nodes, we have to free all B node first
     // free a
     while (head != NULL)
     {
          list_a *next = head->next;
          free(head);
          head = next;
     }
}

void free_b(list_b *head)
{
     while (head != NULL)
     {
          list_b *next = head->next;
          free(head->string);
          free(head);
          head = next;
     }
}