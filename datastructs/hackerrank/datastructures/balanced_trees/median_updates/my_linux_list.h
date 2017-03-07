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
  struct list_head list_var_name = LIST_INIT_HEAD(list_var_name) // No semi-colon here.

#endif