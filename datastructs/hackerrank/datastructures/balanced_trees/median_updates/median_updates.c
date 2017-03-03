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

static inline void INIT_LIST_HEAD(struct list_head *list) { // Using "inline" qualifier allows the compiler to remove the function call overhead for callers of this function.
  // Set next/prev pointers to self.
  // der-note: What if list is null.? Why doesn't linux check?
  list->next = list;
  list->prev = list;
}


int main(void) {

  printf("Hello, World\n");

}