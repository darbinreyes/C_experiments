#include <stdio.h>
#include <assert.h>

/**
### FYI: Linux C style for function comments

###
# Plan:
* Print an array based heap.
* Implement Add().

**/


#define HEAP_ARRAY_SIZE 8

static int heap_array[HEAP_ARRAY_SIZE];
static int heap_entry_count; // Count also == next free spot in the array.

#define PARENT_INDEX(child_index) (((unsigned)child_index & 1U)? (child_index / 2) : (child_index / 2 - 1))
#define LEFT_CHILD_INDEX(parent_index)  (parent_index * 2 + 1)
#define RIGHT_CHILD_INDEX(parent_index) (parent_index * 2 + 2)

/**
  Helper function for the max heap add() operation.
  Bubble up the value at index i_leaf to its proper location
  in the max heap.

  Instead of swapping, we simply copy values downward as the leaf bubbles up.

  Time complexity = O(h). where h = height of the tree = number of levels - 1 = floor(log2(Num. Nodes))

  Returns 0 on success. < 0 otherwise.

**/
int bubble_up(int i_leaf) {

  return 0;
}

/**

**/
int max_heap_add(int d) {

  if(heap_entry_count >= HEAP_ARRAY_SIZE) { // No more space.
    assert(0);
    return -1;
  }

  heap_array[heap_entry_count++] = d;

  if(heap_entry_count == 1) { // First entry in heap. Nothing else to do.
    return 0;
  }

  // Bubble up new entry.

  bubble_up(heap_entry_count - 1);

  return 0;
}

/**

**/
int max_heap_init(void) {
  heap_entry_count = 0;
  return 0;
}

int main(void) {
  int a[] = {7,5,3};
  int a_len = sizeof(a) / sizeof(a[0]);
  int i;

  max_heap_init();
  printf("Hello, max heap.\n");

  return 0;
}

/**
### FYI: Linux C style for function comments


 * list_empty_careful - tests whether a list is empty and not being modified
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * NOTE: using list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
static inline int list_empty_careful(const struct list_head *head)
{
  struct list_head *next = head->next;
  return (next == head) && (next == head->prev);
}
###
 */