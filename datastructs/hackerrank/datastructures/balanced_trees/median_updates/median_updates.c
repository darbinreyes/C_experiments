/**

  https://www.hackerrank.com/challenges/median

**/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "my_linux_list.h"

// ### My linked list code based on above. ###
// AKA insert new in between prev and next. [[before]<->*[new]*<->[after]]
int my_list_sandwhich_add(struct list_head *new, struct list_head *before, struct list_head *after) {
  // link after then link before.
  after->prev = new;
  new->next = after;
  new->prev = before;
  before->next = new;
  return 0;
}

// Add new in between head and head->next. [[head]<->*[new]*<->[head->next]]
int my_list_add_head(struct list_head *head, struct list_head *new) {
  my_list_sandwhich_add(new, head, head->next);
  return 0;
}

// Append to end of given list. [[head->prev]<->*[new]*<->[head]]
int my_list_add_tail(struct list_head *head, struct list_head *new) {
  // 1. case if list empty.
  // 2. case not empty.
  // Q: If head node does not contain data, how do we treat it?
  // ANS: The head just acts as a handle with after_head_node== first node with data. before_head_node=last node with data.
  my_list_sandwhich_add(new, head->prev, head);
  return 0;
}

struct median_updates_node {
  int data;
  int data_count; // Count of instances of same data.
  struct list_head list; //  Same as adding next/prev pointers in this struct. Linux style.
};

#define IS_LIST_EMPTY(list_head_ptr) ((list_head_ptr->next) == (list_head_ptr->prev)) // TRUE if list is empty.

#define byte_offset_of(type_name, member_name) ( ( char * ) &(((struct type_name *)0)->member_name) )
#define container_of(member_ptr, type_name, member_name) ((struct type_name *) ( ( (char *) member_ptr ) - byte_offset_of(type_name, member_name) ) ) // FYI: Adding "(struct type_name *)" got rid of the long vs. pointer type warning.

static int entry_count;
static struct median_updates_node *median_ptr;

// Add new entry to a sorted list at sorted position.
void my_list_add_sorted_increasing(struct list_head *head, struct list_head *new) {
  struct list_head *current_node;
  int count;
  struct median_updates_node *container;

  assert(head != NULL);
  assert(new != NULL);

  if(IS_LIST_EMPTY(head)) {
    // Simply add the new node and return.
    my_list_add_head(head, new);
    return;
  }

  // Handle Tail or head addition. No need to search in this case.
  current_node = head->next;
  container = container_of(current_node, median_updates_node, list);

  if(container_of(new, median_updates_node, list)->data <= container->data) {
    // Head add.
    my_list_add_head(head, new);
    return;
  }

  current_node = head->prev;
  container = container_of(current_node, median_updates_node, list);

  if(container_of(new, median_updates_node, list)->data >= container->data) {
    // Tail add.
    my_list_add_tail(head, new);
    return;
  }

  for(current_node = head->next, count = 0; \
    current_node != NULL && current_node != head; \
    current_node = current_node->next, count++) {

    container = container_of(current_node, median_updates_node, list);
    //printf("%d\n", container->data);
    if(container->data >= container_of(new, median_updates_node, list)->data) {
      my_list_sandwhich_add(new, current_node->prev, current_node);
      return;
    }
  }

  //printf("count = %d.\n", count);
  assert(0);
}

void my_list_add_sorted_increasing_and_update_median(struct list_head *head, struct list_head *new) {
  my_list_add_sorted_increasing(head, new);
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

// prints all entries in the list.
void print_list(struct list_head *head) {
  struct list_head *current_node;
  int count;

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
    // my_list_add_tail(&median_updates_list_head, &m_node->list);
    //my_list_add_sorted_increasing(&median_updates_list_head, &m_node->list);
    my_list_add_sorted_increasing_and_update_median(&median_updates_list_head, &m_node->list);


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