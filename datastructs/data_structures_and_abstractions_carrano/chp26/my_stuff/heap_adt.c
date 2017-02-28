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

// Only valid for child_index > 0
#define PARENT_INDEX(child_index) (((unsigned)child_index & 1U)/*even or odd*/? (child_index / 2) : (child_index / 2 - 1))
#define LEFT_CHILD_INDEX(parent_index)  (parent_index * 2 + 1)
#define RIGHT_CHILD_INDEX(parent_index) (parent_index * 2 + 2)
#define SIBLING_INDEX(sib_index) (((unsigned)sib_index & 1U)/*even or odd*/? (sib_index + 1) : (sib_index - 1))

/**
  Helper function for the max heap add() operation.
  Bubble up the value at index i_leaf to its proper location
  in the max heap.

  Instead of swapping, we simply copy values downward as the leaf bubbles up.

  Time complexity = O(h). where h = height of the tree = number of levels - 1 = floor(log2(Num. Nodes))

  Returns 0 on success. < 0 otherwise.

**/
static int bubble_up(int i_leaf, int d_leaf) {
  int i_parent;

  if(i_leaf == 0) {// This is the root. No-op.
    assert(0);
    return -1;
  }

  //printf("i_leaf = %d. d_leaf = %d.\n", i_leaf, d_leaf);

  i_parent = PARENT_INDEX(i_leaf);
  //printf("i_parent = %d.\n", i_parent);
  assert(i_parent >= 0);

  while(heap_array[i_parent] < d_leaf) {
    // Copy parent value downward.
    heap_array[i_leaf] = heap_array[i_parent];
    i_leaf = i_parent;

    if(i_leaf == 0) // We reached the root.
      break;

    i_parent = PARENT_INDEX(i_leaf);
    assert(i_parent >= 0);
  }

  assert(i_leaf >= 0);
  heap_array[i_leaf] = d_leaf;

  return 0;
}

/**

**/
static int max_heap_add(int d) {

  if(heap_entry_count >= HEAP_ARRAY_SIZE) { // No more space.
    assert(0);
    return -1;
  }

  //printf("Add. d = %d.\n", d);

  heap_array[heap_entry_count++] = d;

  if(heap_entry_count == 1) { // First entry in heap. Nothing else to do.
    return 0;
  }

  // Bubble up new entry.

  bubble_up(heap_entry_count - 1, d);

  return 0;
}

/**

  Given a parent_index, returns the index of the child with the larger value.

  Returns >= 0 if successful, < - otherwise, e.g. if parent_index does not have
  children.

**/
int max_child_index(int *a, int parent_index, int len) {
  int i_left, i_right;

  assert(parent_index >= 0);

  if(parent_index >= len - 1) // No children.
    return -1;

  i_left = LEFT_CHILD_INDEX(parent_index);
  i_right = RIGHT_CHILD_INDEX(parent_index);

  if(i_left < len && i_right < len) // Has 2 children
    return ((a[i_left] >= a[i_right])? i_left : i_right);

  // Has 1 child.

  if(i_left < len)
    return i_left;

  if(i_right < len)
    return i_right;

  return -2;
}

/**

  Given a semi-heap, performs a re-heap, AKA sinks the root down toward largest
  child.

**/
int max_heap_reheap(int d_leaf) { // Form a semi-heap by moving the last leaf to the root position.

  int i_root, i_max_child;

  assert(heap_entry_count != 0);

  if(heap_entry_count == 1) { // Re-heaping 1 entry heap, just copy leaf to root.
    heap_array[0] = d_leaf;
    return 0;
  }

  i_root = 0; // Sink d_leaf starting at the root.
  i_max_child = max_child_index(heap_array, i_root, heap_entry_count);

  while(i_max_child >= 0 && i_max_child  < heap_entry_count && heap_array[i_max_child] > d_leaf) {
    heap_array[i_root] = heap_array[i_max_child]; // Copy larger child value up.
    i_root = i_max_child;
    i_max_child = max_child_index(heap_array, i_root, heap_entry_count);

    if(i_max_child < 0) {
      break;
    }
  }

  heap_array[i_root] = d_leaf;

  return 0;
}

/**

  Removes and returns the max value from the max heap. By definition, the max value
  is always at the root of the heap's bin. tree.

  If the heap is empty, this is a no-op. -1 is returned.
  If the heap contains only a single value then it is returned and were done.
  Otherwise, we need to adjust the entries to maintain the max heap contraint,
  i.e. the root is always greater than or equal to its children, this must
  be true at all nodes(recursively true).
  Removal of the root value is done by replacing it with the last leaf value and
  then allowing the value to sink towards *larger* values. AKA "re-heaping".
  This operation is has a time complexity of O(log2(Num. Nodes)) = O(Bin. tree Height)
  , worst case.

  If successful, the max is returned in *d, and the function returns 0. < 0 otherwise.


**/
int max_heap_remove_max(int *d) {
  assert(d != NULL);
  assert(heap_entry_count > 0);

  if(d == NULL) { // Invalid arg.
    return -1;
  }

  if(heap_entry_count <= 0) { // Heap is empty.
    return -2;
  }

  *d = heap_array[0]; // Return the max value, which is always at the root.
  --heap_entry_count;
  if(heap_entry_count == 0) // No need to re-heap an empty heap. Silly.
    return 0;

  // Need to re-heap.
  max_heap_reheap(heap_array[heap_entry_count]);

  return 0;
}

/**

  Generalized max_heap_reheap().

**/
int max_heap_reheap2(int *a, int len) { // Form a semi-heap by moving the last leaf to the root position.

  int i_root, i_max_child, d_leaf;

  assert(a != NULL);
  assert(len > 0);

  if(a == NULL || len <= 0)
    return -1;

  if(len == 1) { // Re-heaping 1 entry heap, no-op.
    return 0;
  }

  d_leaf = a[0];
  i_root = 0; // Sink d_leaf starting at the root.
  i_max_child = max_child_index(a, i_root, len);

  while(i_max_child >= 0 && i_max_child  < len && a[i_max_child] > d_leaf) {
    a[i_root] = a[i_max_child]; // Copy larger child value up.
    i_root = i_max_child;
    i_max_child = max_child_index(a, i_root, len);

    if(i_max_child < 0) {
      break;
    }
  }

  a[i_root] = d_leaf;

  return 0;
}

/**

**/
int create_max_heap(int *a, int a_len) {
  int i, p = 0;

  assert(a != NULL);
  assert(a_len > 0);

  if(a == NULL || a_len <= 0)
    return -1;

  if(a_len == 1) { // Single entry in max heap. No extra work necessary. Done.
    return 0;
  }

  i = a_len - 1; // i = root of current subtree. Start from parent of last leaf.
  i = PARENT_INDEX(i);

  // Re-heap along the path up towards the root.
  // End result is a max heap in O(n) time complexity.

  while(i >= 0 && i < a_len) {
    max_heap_reheap2(&a[i], a_len - i);
    if(i <= 0)
      break;
    else {
      i--;
    }
  }

  return 0;
}


/**

**/
int max_heap_init(void) {
  heap_entry_count = 0;
  return 0;
}

void print_heap_array(int *a, int len) {
  int i;

  assert(a != NULL);
  assert(len >= 0);

  //printf("len = %d.\n", len);

  if(len == 0) {
    printf("EMPTY.\n");
    return;
  }

  // for(int i = 0; i < len - 1; i++) // holy fuck!! bug !!! - int re-defined as block local, vs definition at the start of the function which is a different storage location.
  for(i = 0; i < len - 1; i++)
    printf("%d ", a[i]);

  printf("%d\n", a[i]);

}

int main(void) {
  int a[] = {7,5,3, 8, 9};
  int a_len = sizeof(a) / sizeof(a[0]);
  int i, t;

  printf("Hello, max heap. a_len = %d.\n", a_len);


  max_heap_init();


  print_heap_array(heap_array, heap_entry_count);

  for(int i = 0; i < a_len; i++) {
    max_heap_add(a[i]);
    print_heap_array(heap_array, heap_entry_count);
  }

  print_heap_array(heap_array, heap_entry_count);

  t = -13;
  max_heap_remove_max(&t);

  printf("Removed max = %d.\n", t);

  print_heap_array(heap_array, heap_entry_count);

  t = -13;
  max_heap_remove_max(&t);

  printf("Removed max = %d.\n", t);

  print_heap_array(heap_array, heap_entry_count);
  t = -13;
  max_heap_remove_max(&t);

  printf("Removed max = %d.\n", t);

  print_heap_array(heap_array, heap_entry_count);

  printf("Creating max heap.\n");

  print_heap_array(a, a_len);

  create_max_heap(a, a_len);

  print_heap_array(a, a_len);

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