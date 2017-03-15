/**

  https://www.hackerrank.com/challenges/median

**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "my_linux_list.h"

// ### My linked list code based on above. ###
// AKA insert new in between prev and next. [[before]<->*[new]*<->[after]]
int my_list_insert(struct list_head *new, struct list_head *before, struct list_head *after) {
  // link after then link before.
  after->prev = new;
  new->next = after;
  new->prev = before;
  before->next = new;
  return 0;
}

// Add new in between head and head->next. [[head]<->*[new]*<->[head->next]]
int my_list_add_head(struct list_head *head, struct list_head *new) {
  my_list_insert(new, head, head->next);
  return 0;
}

// Append to end of given list. [[head->prev]<->*[new]*<->[head]]
int my_list_add_tail(struct list_head *head, struct list_head *new) {
  // 1. case if list empty.
  // 2. case not empty.
  // Q: If head node does not contain data, how do we treat it?
  // ANS: The head just acts as a handle with after_head_node== first node with data. before_head_node=last node with data.
  my_list_insert(new, head->prev, head);
  return 0;
}

struct median_updates_node {
  int data;
  int data_count; // Count of instances of same data.
  struct list_head list; //  Same as adding next/prev pointers in this struct. Linux style.
};


static int entry_count;
static struct median_updates_node *median_ptr;

// Compares to median_updates_node's. Returns > 0 if a > b, Return == 0 if a == b. and Returns < 0 if a < b.
typedef int (*list_node_cmp_func)(struct list_head *a_node, struct list_head *b_node);

// Add new entry to a sorted list at sorted position.
void my_list_add_sorted_increasing(struct list_head *head, struct list_head *new, list_node_cmp_func cmp_func) {
  struct list_head *current_node;
  int count;

  assert(head != NULL);
  assert(new != NULL);
  assert(cmp_func != NULL);

  if(IS_LIST_EMPTY(head)) {
    // Simply add the new node and return.
    my_list_add_head(head, new);
    return;
  }

  //
  // Handle Tail or head addition. No need to search in this case.
  //

  current_node = head->next; // Get head node
  // Check if new is smaller than the head. If yes, insert new before current head and return.
  if(cmp_func(new, current_node) < 0) {
    my_list_add_head(head, new);
    return;
  }

  current_node = head->prev; // Get tail node.
  // Check if new is greater than the tail node. If yes, add new after current tail and return.
  if(cmp_func(new, current_node) > 0) {
    my_list_add_tail(head, new);
    return;
  }

  for(current_node = head->next; current_node != NULL && current_node != head; current_node = current_node->next) {

    // Find the first node that is greater than or equal to new.

    if(cmp_func(new, current_node) <= 0) {
      break;
    }
  }

  // Insert immediately before the bigger or equal node and return.
  my_list_insert(new, current_node->prev, current_node);
  return;
}

static int median_node_cmp_func(struct list_head *a, struct list_head *b) {
  struct median_updates_node *a_node, *b_node;

  assert(a != NULL && b != NULL);

  a_node = container_of(a, median_updates_node, list);
  b_node = container_of(b, median_updates_node, list);

  return a_node->data - b_node->data;
}

static void my_list_add_sorted_increasing_and_update_median(struct list_head *head, struct list_head *new) {
  my_list_add_sorted_increasing(head, new, median_node_cmp_func);
  // assume add is always successful for now.
  entry_count++;

  if(median_ptr == NULL) {
    assert(entry_count == 1);
    median_ptr = container_of(new, median_updates_node, list);
    return;
  }

  // Update median.
  if(entry_count % 2 == 0 || entry_count <= 3) { // even count.
    // no-op.
    return;
  }

  // odd count.

  if(container_of(new, median_updates_node, list)->data >= median_ptr->data){
    // new node added after current median. move median up one node. // TEST THIS.
    median_ptr = container_of(median_ptr->list.next, median_updates_node, list);
  } else {
    median_ptr = container_of(median_ptr->list.prev, median_updates_node, list);
  }

}

#define my_list_for_each(container_ptr, head_ptr, container_type, list_member) \
  for(struct list_head *current_node = head_ptr->next; current_node != head_ptr && (container_ptr = container_of(current_node, container_type, list_member)); current_node = current_node->next)

// prints all entries in the list.
void print_list(struct list_head *head) {
  struct list_head *current_node;
  int count;
  struct median_updates_node *mu_node_ptr;

  assert(head != NULL);

  // if(head->next == head->prev) { // TODO: compare with linux.
  //   printf("EMPTY.\n");
  //   return;
  // }

  for(current_node = head->next, count = 0; \
    current_node != NULL && current_node != head; \
    current_node = current_node->next, count++) {
    //
    // How to get container of list from list? i.e. implement container_of()
    // GUESS: from address of list member, subtract a number of bytes such that
    // the result of the difference with point to the first byte of the container.
    // address_of_container_struct_member - (distance between start of container struct to struct member.)
    //
    // ((char *)current_node) - ( ((char *) (&((struct median_updates_node *)0)->list))) )
    // byte_offset_of(type_name, member_name) ( ( char * ) &(((struct type_name *)0)->member_name) )
    //
    struct median_updates_node *container = container_of(current_node, median_updates_node, list);//( ( char * ) current_node ) - ( ( char * ) &(((struct median_updates_node *)0)->list) );
    printf("%d\n", container->data);
  }

  // macro based iteration
  my_list_for_each(mu_node_ptr, head, median_updates_node, list) {
    printf("x %d\n", mu_node_ptr->data);
  }

  //printf("count = %d.\n", count);
}



LIST_HEAD(median_updates_list_head);

int main(void) {
  int a[] = {7, 5, 9, 3, 2, 13, 21, 6};
  int i;
  struct median_updates_node *m_node;

  printf("Hello, World\n");

  print_list(&median_updates_list_head);

  for(i = 0; i < ARRAY_SIZE(a); i++) {
    m_node = malloc(sizeof(*m_node));
    assert(m_node != NULL);
    m_node->data = a[i];
    m_node->data_count = 1; // Assumes a[] does not contain duplicates.
    INIT_LIST_HEAD(&m_node->list);

    my_list_add_sorted_increasing(&median_updates_list_head, &m_node->list, median_node_cmp_func);

    //my_list_add_sorted_increasing_and_update_median(&median_updates_list_head, &m_node->list);


    print_list(&median_updates_list_head);
    printf("entry_count = %d.\n", entry_count);
    if(entry_count % 2 != 0)
      printf("median = %d.\n", median_ptr->data);
    //else // avg. for even median.
      //printf("median = %d// ".5".\n", median_ptr->data);
  }

  print_list(&median_updates_list_head);

  // Print nodes.

  for(i = 0; i < ARRAY_SIZE(a); i++) {
    // TODO: free() nodes.
  }

}