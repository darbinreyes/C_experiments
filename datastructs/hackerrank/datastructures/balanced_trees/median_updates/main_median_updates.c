/**

  https://www.hackerrank.com/challenges/median

**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "my_linux_list.h"

struct median_updates_node {
  int data;
  int data_count; // Count of instances of same data.
  struct list_head list; //  Same as adding next/prev pointers in this struct. Linux style.
};

// Provider O(1) access to computation of median value in the list. Points to
// the center node in the sorted list. If the list length is odd, it points to
// the node at index len(list)/2+1. Index is 0 based. If the list length is
// even, points to the node at index len(list)/2. Index is 0 based. If the list
// is empty, points to NULL. Otherwise, the pointer is adjusted after each
// add/remove. By comparing the value of the added/removed node, where known on
// which side the add/remove occurred  relative to the current median node, e.g.
// if the current len is 4, and we add a new value at the end of the list, then
// the current median pointer should be adjusted to point to the median_node_ptr->next.
//
static struct median_updates_node *median_node_ptr;

// Adds an entry to the list at its sorted location.
// Pre-condition: The input list must already be sorted.
// Post-condition: The list after inserting the specified entry at its sorted position.
// @data: The data member value for the new entry.
// @head: The head/handle of the list to add to.
// Time Complexity: O(n)
int median_updates_list_add_sorted(int data, struct list_head *head);

// Removes an entry from the list.
// Pre-condition: The input list must already be sorted.
// Post-condition: The list after removing the entry with the specified value. If more than one instance of data exists in the list then the node is only the count is 0 after decrementing it.
// @data: The data member value for the entry to remove.
// @head: The head/handle of the list to remove from.
// Time Complexity: O(n)
int median_updates_list_remove_sorted(int data, struct list_head *head);



LIST_HEAD(median_updates_list_head);

int main(void) {

  printf("Hello, World\n");

}