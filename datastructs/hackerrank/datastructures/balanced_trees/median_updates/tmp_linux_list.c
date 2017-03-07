/// #####
/**
 * list_entry - get the struct for this entry
 * @ptr:  the &struct list_head pointer.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
  container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:  the list head to take the element from.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
  list_entry((ptr)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * @ptr:  the list head to take the element from.
 * @type: the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(ptr, type, member) \
  list_entry((ptr)->prev, type, member)
/**
 * list_for_each_entry  - iterate over list of given type
 * @pos:  the type * to use as a loop cursor.
 * @head: the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)        \
  for (pos = list_first_entry(head, typeof(*pos), member);  \
       &pos->member != (head);          \
       pos = list_next_entry(pos, member))
/// #####