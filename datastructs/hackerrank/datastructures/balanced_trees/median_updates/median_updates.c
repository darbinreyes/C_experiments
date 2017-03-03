/**

  https://www.hackerrank.com/challenges/median

**/

#include <stdio.h>

// My copy Linux impl. of circular doubly linked list.

struct list_head {
  struct list_head *next, *prev;
};

struct median_updates_node {
  int data;
  int data_count; // Count of instances of same data.
  struct list_head list; //  Same as adding next/prev pointers in this struct. Linux style.
};

// Sets next/prev pointers to address of self.
#define LIST_HEAD_INIT(list_var_name) { &(list_var_name), &(list_var_name) } // DONT FORGET TO USE PAREN.S IN ALL DEFINES.

#define LIST_HEAD(list_var_name) \
  struct list_head list_var_name = LIST_INIT_HEAD(list_var_name) // No semi-colon here.

static inline void INIT_LIST_HEAD(struct list_head *list) { // Notice this is a private (static) function in the LINUX header, but it is available publicly because the function is defined in the header that is included by clients. Using "inline" qualifier allows the compiler to remove the function call overhead for callers of this function.
  // Set next/prev pointers to self.
  // der-note: What if list is null.? Why doesn't linux check?
  list->next = list;
  list->prev = list;
}

// ### My linked list code based on above. ###
int my_list_sandwhich_add(struct list_head *new, struct list_head *before, struct list_head *after) {
  // link after then link before.
  after->prev = new;
  new->next = after;
  new->prev = before;
  before->next = new;
  return 0;
}
// Append to end of given list.

int my_list_add_tail(struct list_head *head, struct list_head *new) {
  // 1. case if list empty.
  // 2. case not empty.
  // Q: If head node does not contain data, how do we treat it?
  // ANS: The head just acts as a handle with after_head_node== first node with data. before_head_node=last node with data.
  my_list_sandwhich_add(new, head->prev, head);
  return 0;
}


int main(void) {

  printf("Hello, World\n");

}