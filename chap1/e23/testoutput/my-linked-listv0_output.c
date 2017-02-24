




#include <stdio.h>
#include <stdlib.h>

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

    
    destroyLinkedList(&ll);
    printf("After destroy. len = %d\n", getLength(&ll));


    return 0;
}



int createLinkedList(LINKED_LIST *ll){
    if(ll == NULL)
        return -1;

    ll->head = NULL;

    return 0;
}


int addNode(LINKED_LIST *ll, int data) {
    LIST_NODE *newNode, *n; 
    
    if(ll == NULL)
        return -1;

    
    newNode = (LIST_NODE *) malloc(sizeof(LIST_NODE));
    if(newNode == NULL)
        return -1;

    
    newNode->data = data;
    newNode->next =  NULL;

    
    if(ll->head == NULL) {
        ll->head = newNode;
        return 0;
    }

    

    
    for(n = ll->head; n->next != NULL; n = n->next)
        ;

    
    
    

    n->next = newNode;
    return 0;
}




int getLength(LINKED_LIST *ll) {
    int len;
    LIST_NODE *n;

    if(ll == NULL)
        return -1;

    if(ll->head == NULL)
        return 0;

    
    
    
    len = 1; 
    n = ll->head;
    while((n = n->next) != NULL)
        len++; 

    return len;
}




int removeNode(LINKED_LIST *ll) {
    LIST_NODE *n, *prev;
    int len;

    if(ll ==  NULL)
        return -1;

    if(ll->head == NULL) 
        return 0;

    len = 1;
    
    
    n = ll->head;
    prev = NULL;

    while(n->next != NULL){ 
        prev = n; 
        n = n->next;
        len++;
    }

    if(prev != NULL) {
        free(prev->next);
        prev->next = NULL;
    } else { 
        free(n);
        ll->head = NULL;
    }

    return --len; 
}


int destroyLinkedList(LINKED_LIST *ll) {

    if(ll == NULL)
        return -1;

   
    while(removeNode(ll) > 0)
        ;

    return 0;
}
