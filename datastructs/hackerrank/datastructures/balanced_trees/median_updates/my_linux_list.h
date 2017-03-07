/**
  My implementation of a doubly linked list based on how Linux does it.
**/

#ifndef __MY_LINUX_LIST_H__
#define __MY_LINUX_LIST_H__

// List node definition.
struct list_head {
  struct list_head *next, *prev;
};

// Sets next/prev pointers to address of self.
#define LIST_HEAD_INIT(list_var_name) { &(list_var_name), &(list_var_name) } // DONT FORGET TO USE PAREN.S IN ALL DEFINES.

// Declares a list head/handle.
#define LIST_HEAD(list_var_name) \
  struct list_head list_var_name = LIST_HEAD_INIT(list_var_name) // No semi-colon here.

static inline void INIT_LIST_HEAD(struct list_head *list) { // Notice this is a private (static) function in the LINUX header, but it is available publicly because the function is defined in the header that is included by clients. Using "inline" qualifier allows the compiler to remove the function call overhead for callers of this function.
  // Set next/prev pointers to self.
  // der-note: What if list is null.? Why doesn't linux check?
  list->next = list;
  list->prev = list;
}

#endif