/**
  My implementation of a doubly linked list based on how Linux does it.
**/

#ifndef __MY_LINUX_LIST_H__
#define __MY_LINUX_LIST_H__

// TODO: Compare this to linux impl.
#define IS_LIST_EMPTY(list_head_ptr) ( (list_head_ptr == list_head_ptr->next) && ( (list_head_ptr->next) == (list_head_ptr->prev) ) ) // TRUE if list is empty.

// List node definition. // My copy Linux impl. of circular doubly linked list.

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

/** Misc. Definitions, not just list related. **/

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0])) // My array size #define

#define byte_offset_of(type_name, member_name) ( ( char * ) &(((struct type_name *)0)->member_name) )
#define container_of(member_ptr, type_name, member_name) ((struct type_name *) ( ( (char *) member_ptr ) - byte_offset_of(type_name, member_name) ) ) // FYI: Adding "(struct type_name *)" got rid of the long vs. pointer type warning.


#endif