/*
A basic linked list implementation. 
Nodes only support int data, and are singly linked. Only a pointer to the head
is maintained by the list struct. 

Operations supported:

addNode
removeNode
getLength

############
What would it look like in Java?

LINKED_LIST<Integer> myll = new LinkedList<Integer>(); // constructs a new linked list object with 0 nodes. // Can we do something similar to <Integer> in C?
printf("Length = %d", myll.getLength()); // prints Length = 0
myll.addNode(3);
printf("Length = %d", myll.getLength()); // prints Length = 1
myll.addNode(2);
printf("Length = %d", myll.getLength());
myll.addNode(1);
printf("Length = %d", myll.getLength());
myll.removeNode(); // deletes the node at the end of the list. 
printf("Length = %d", myll.getLength());

// Java garbage collector cleans up for you.
############
Example usage:
LINKED_LIST myll; // how can we make the head pointer private?

createLinkedList(&myll); // Initializes head to null. 

addNode(&myll, 3); // Add a node with data  = 3, mem. for the new node is allocated using malloc(). 
printf("Length = %d", getLength(myll)); // prints Length = 1. getLength(myll) will walk from the head to the end of the list to determine the current count. We can optimize later. 

...etc.
removeNode(&myll); // walks to the end of the list, unlinks that node, free's the nodes memory. 
*/


/*

The following typedef generates a compiler error because 
you are using the LIST_NODE typedef before it has been declared. 
Recall that in C your allowed to define self referential structs 
but not in this manner. 

darbinreyessmbp:datastructs darbinreyes$ cc my-linked-list.c 
my-linked-list.c:44:5: error: unknown type name 'LIST_NODE'
    LIST_NODE *next;
    ^
1 error generated.
Another legal way to declare such a referential struct would be as follows. 

typedef struct _LIST_NODE {
    int data;
    struct _LIST_NODE *next;
} LIST_NODE;

There is another way, it is a common idiom seen in UEFI protocol headers, called 
a forward declaration. 

///
/// Forward declaration
///
typedef struct _PROTOCOL PROTOCOL;

Note that this is a typedef, not a #define. It means, let me use the word "PROTOCOL" 
for the type of a variable and take it to mean the same as "struct _PROTOCOL". 
Thus in:

struct _PROTOCOL a;
PROTOCOL b;

a and b have the same type. Note that struct _PROTOCOL can be used before it has been
defined. This is a rare exception in C. 

struct _PROTOCOL should be defined without a typedef after the forward declaration,
otherwise you will get a compiler warning as show below. 

typedef struct _LIST_NODE LIST_NODE; // generates a redefinition warning

typedef struct _LIST_NODE {
    int data;
    LIST_NODE *next;
} LIST_NODE; // You redefined LIST_NODE!

my-linked-list.c:85:3: warning: redefinition of typedef 'LIST_NODE' is a C11 feature [-Wtypedef-redefinition]
} LIST_NODE;
  ^
my-linked-list.c:80:27: note: previous definition is here
typedef struct _LIST_NODE LIST_NODE;
                          ^
1 warning generated.

The correct idiom would be:

typedef struct _LIST_NODE LIST_NODE;

struct _LIST_NODE {
    int data;
    LIST_NODE *next;
};

*/

#include <stdio.h>
#include <stdlib.h>
// http://cslibrary.stanford.edu//103/
typedef struct _LIST_NODE LIST_NODE;

struct _LIST_NODE {
    int data;
    LIST_NODE *next;
};

typedef struct _LINKED_LIST {
    LIST_NODE *head;
} LINKED_LIST;

int createLinkedList(LINKED_LIST *ll);
int addNode(LINKED_LIST *ll, int data);
int getLength(LINKED_LIST *ll);
int removeNode(LINKED_LIST *ll);
int destroyLinkedList(LINKED_LIST *ll);

int main(void) {
    LINKED_LIST ll;

    printf("Hello, World. Linked list.\n");

    createLinkedList(&ll);
    printf("len = %d\n", getLength(&ll));
    addNode(&ll, 2);
    printf("len = %d\n", getLength(&ll));
    addNode(&ll, 3);
    printf("len = %d\n", getLength(&ll));
    addNode(&ll, 5);
    printf("len = %d\n", getLength(&ll));

    // cleanup and summary. 
    destroyLinkedList(&ll);
    printf("After destroy. len = %d\n", getLength(&ll));


    return 0;
}


// init. a new linked list. returns 0 on success, -1 on failure.
int createLinkedList(LINKED_LIST *ll){
    if(ll == NULL)
        return -1;

    ll->head = NULL;

    return 0;
}

// add a node to the linked list. returns 0 on success, -1 on failure. 
int addNode(LINKED_LIST *ll, int data) {
    LIST_NODE *newNode, *n; // observe the "*" needs to be added for each variable in a declaration - "*" is not transitive? like type.
    
    if(ll == NULL)
        return -1;

    // create the new node with the specified data. 
    newNode = (LIST_NODE *) malloc(sizeof(LIST_NODE));
    if(newNode == NULL)
        return -1;

    // init. fields in the new node.
    newNode->data = data;
    newNode->next =  NULL;

    // check for an empty list, if empty, create and set the head. 
    if(ll->head == NULL) {
        ll->head = newNode;
        return 0;
    }

    // append the new node to the end of the list. 

    // find the end of the list. 
    for(n = ll->head; n->next != NULL; n = n->next)
        ;

    // the for loop above will start at the head and go to the next node as long
    // a next node exists (!=null). When n->next == NULL, we know n is the last node. 
    // which is where we want to add our new node. 

    n->next = newNode;
    return 0;
}

// returns the length of a linked list. 
// returns the length on success, -1 on failure. ll == null is an error.
// The length is defined as the number of nodes in the list, including the head. 
int getLength(LINKED_LIST *ll) {
    int len;
    LIST_NODE *n;

    if(ll == NULL)
        return -1;

    if(ll->head == NULL)
        return 0;

    // increment the length each time we encounter a new node.
    // A new is encountered each time n->next != NULL.
    // use a while loop for fun. 
    len = 1; // start at 1 since the head is included in the length
    n = ll->head;
    while((n = n->next) != NULL)
        len++; 

    return len;
}

// removes a node from the end of the list. 
// returns the new length on success, -1 on failure. ll == null is an error.
// removing a node from an empty list is a no-op. 0 will be returned in this case.
int removeNode(LINKED_LIST *ll) {
    LIST_NODE *n, *prev;
    int len;

    if(ll ==  NULL)
        return -1;

    if(ll->head == NULL) // no-op. 
        return 0;

    len = 1;
    // Find the node that precedes the tail node (second to last).
    // Free the tail node. return.
    n = ll->head;
    prev = NULL;

    while(n->next != NULL){ 
        prev = n; // prev is always one node behind n. 
        n = n->next;
        len++;
    }

    if(prev != NULL) {
        free(prev->next);
        prev->next = NULL;
    } else { // We never entered the loop. ll contains only one node. 
        free(n);
        ll->head = NULL;
    }

    return --len; // the new length after removing one node.
}

// free all memory allocated for the linked list. returns 0 on success, -1 on error.
int destroyLinkedList(LINKED_LIST *ll) {

    if(ll == NULL)
        return -1;

   
    while(removeNode(ll) > 0)
        ;

    return 0;
}
