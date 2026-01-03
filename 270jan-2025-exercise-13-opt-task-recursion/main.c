// Write a C function that given a set of tasks, each one with a time duration and a priority, selects the subset of those
// tasks whose total duration time is less or equal to a given threshold while maximizing the sum of the priorities. The
// prototype of the function is the following:
// void opt_task (int n, int *time, int *priority, int th, int *best, int *l, int *max);
// In the prototype, the following are input parameters: Variable n is the number of tasks, time the array expresses
// their duration (in hours), and priority the array indicates their priorities (or their rewards, once solved). In the
// prototype, the output parameters are the following: The array best specifies the selected tasks (their indices in the
// time and priority arrays), the number of tasks assigned and stored into best, l, and the variable max storing
// the sum of the tasks’ priorities (i.e., the total reward obtained from their selection).
// For example, let us suppose that n = 4, times = {2, 3, 4, 5}, priority = {3, 4, 5, 8}, and th = 7.
// The function should select tasks 0 and 3 whose times are 2 and 5, have a sum 2 + 5 = 7 ≤ th, and a total priority
// (reward) of 3 + 8 = 11. Thus, it should return best = {0, 3}, l = 2, and max = 11.
// Function opt
// task can be considered a wrapper defining other objects (such as the current solution array and size)
// and calling the actual recursive function (e.g., opt
// task
// r).


#include <stdio.h>

void opt_task(int n, int* time, int* priority, int th, int* best, int* l, int* max);

int main(void)
{
     int n = 4;
     int time[] = {2, 3, 4, 5};
     int priority[] = {3, 4, 5, 8};
     opt_task(n, time, priority, 7, time, time, time);

     return 0;
}

void opt_task(int n, int* time, int* priority, int th, int* best, int* l, int* max)
{
     int curr
     // total duration <= th while max priority sum

}
