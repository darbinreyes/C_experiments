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
    struct median_updates_node *container = ( ( char * ) current_node ) - ( ( char * ) &(((struct median_updates_node *)0)->list) );
    printf("%d\n", container->data);
  }

  printf("%d\n", count);
}

LIST_HEAD(median_updates_list_head);

int main(void) {
  int a[] = {7, 5, 9, 3, 2, 13};
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
    my_list_add_tail(&median_updates_list_head, &m_node->list);
  }

  print_list(&median_updates_list_head);

  // Print nodes.

  for(i = 0; i < ARRAY_SIZE(a); i++) {
    // TODO: free() nodes.
  }

}