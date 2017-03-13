/*

Second call with Amazon, 3/9/2017.

Ashly:

Q1: Describe a project you've worked on. ANS: BIOS config. dependencies encoded as a graph. vs. hard-coded table.

Q2: Describe how you handled a disagreement while working on a project and how you handled the situation. ANS: UTF-8 vs Unicode disagreement with Architect. I explained my reasoning, he disagreed. I just let it go because he was my superior.

Q3: Describe a time when you stood up for customer quality standards. ANS: Few weeks ago, storage controller config. through REST API. I realized there was a potential sec. hole : device driver is allowed to use BIOS proxy to BMC without explicit verification of device driver origin (could be an evil driver).

Q4:
// POST interview - second idea - implement helper function // int get_value(node* head); // This could be way way slower though.
"""
Given a singly linked list, determine if it is a palindrome. Return 1 or 0 denoting if it is a palindrome or not, respectively.

List 1–>2–>1 is a palindrome.
List 1–>2–>3 is not a palindrome.
List 8->4->5->7->5->4->8 is a palindrome.
List 6->4->5->1 is not a palindrome
"""

*/

#include <stdio.h>

typedef struct _LIST_NODE {
 int data;
 struct _LIST_NODE *next;
} LIST_NODE;

// 1 means its a palind. 0 otherwise.
int is_list_palind (LIST_NODE *head) {
  int n, i, j;
  LIST_NODE *right_end, *left_end, *current_node, *current_node2;
  
  // empty is not a palind
  if(head == NULL)
    return 0;
    
  // 1 node is a palind.
  if(head->next == NULL)
    return 1;
    
    
  // Determine list len.
  for(current_node = head, n = 0; current_node != NULL; current_node = current_node->next, n++)
    ;
  
  // Find the right half of the list.  


  //POST interview: found bug in upper limit for i when n is even. My correction : "i < (n/2+(n%2))"
  //for(current_node = head, i = 0; current_node != NULL && i < n/2+1; current_node = current_node->next, i++)
  //    ;
  for(current_node = head, i = 0; current_node != NULL && i < n/2+(n%2); current_node = current_node->next, i++)
    ;///!!!this colon is crucial!
      
  right_end = current_node;
  
  // find the node right before the center node.
  
  
  for(current_node2 = right_end, i = 0; current_node2 != NULL; current_node2 = current_node2->next, i++) {
      for(current_node = head, j = 0; current_node != NULL && j < n/2 - 1 - i; current_node = current_node->next, j++)
        ;
       // cmp right end node to left end node.
      if(current_node2->data != current_node->data)
        return 0;
  }
  
  return 1;
}
// POST interview test case.
int main(void) {
  LIST_NODE list0[] = {{1, &list0[1]},{2, &list0[2]}, {1, NULL}};
  LIST_NODE list1[] = {{1, &list1[1]},{2, &list1[2]}, {2, &list1[3]},{1, NULL}};
  LIST_NODE list2[] = {{1, &list2[1]},{2, &list2[2]}, {7, &list2[3]}, {2, &list2[4]}, {1, NULL}};
  LIST_NODE list3[] = {{1, &list3[1]},{2, &list3[2]}, {7, &list3[3]}, {2, &list3[4]}, {3, NULL}};

  //LIST_NODE list1[] = {{1, &list1[1]},{2, &list1[2]},{2, &list1[3]},{1, NULL}};

  printf("FUK! U! is_list_palind = %d.\n", is_list_palind(list0)); // This test case passed my brain execution+state table test. AND IT WORKED IN COMPUTER EXECUTION!!!
  printf("FUK! U! is_list_palind = %d.\n", is_list_palind(list1)); // Even len. list test case failed. Only off in a single upper limit expression, see above. Fix: replace "+1" "+(n%2)"
  printf("FUK! U! is_list_palind = %d.\n", is_list_palind(list2));
  printf("FUK! U! is_list_palind = %d.\n", is_list_palind(list3));

  return 0;
}