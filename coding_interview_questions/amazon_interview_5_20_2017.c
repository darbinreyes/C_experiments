

#include <stdio.h>



/**

// My original declaration for node

typedef struct {
    int data;
    LIST_NODE *next;
} LIST_NODE;

// START: My KNR simple decl, self ref struct.

// KNR correct, simple declaration. Use "struct" keyword + name tag b
typedef struct _LIST_NODE {
    int data;
    struct _LIST_NODE *next; // CORRECT
    // _LIST_NODE *next; // COMPILER ERROR "error: must use 'struct' tag to refer to type '_LIST_NODE'". "struct" keyword before the struct "Tag" is required.
    // LIST_NODE *next; // COMPILER ERROR "error: unknown type name 'LIST_NODE'", you haven't finished defining LIST_NODE yet, so the compiler can't resolve this type. "struct _LIST_NODE" is OK.
} LIST_NODE;

// END: My KNR

///// UEFI START: typical self ref. struct decl:

typedef struct _EFI_HP_RIS_REST_PROTOCOL EFI_HP_RIS_REST_PROTOCOL;
typedef
EFI_STATUS
(EFIAPI *EFI_HP_RIS_BLOB_WRITE)(
  IN      CONST EFI_HP_RIS_REST_PROTOCOL *This,
  IN      CONST CHAR8                    *BlobNamespace,
  IN      CONST CHAR8                    *BlobName,
  IN      CONST CHAR8                    *BlobEtag, OPTIONAL
  IN      CONST CHAR8                    *BlobIfNoneMatch, OPTIONAL
  IN      CONST CHAR8                    *BlobData,
  IN      UINT32                         BlobSize,
  IN      BOOLEAN                        UseFaf
  );

///
///  Prototype of RIS REST Protocol
///
struct _EFI_HP_RIS_REST_PROTOCOL {
  EFI_HP_RIS_BLOB_WRITE                  RisBlobWrite;
};

////// UEFI END :


**/

// Forward decl.
typedef struct _LIST_NODE LIST_NODE;

struct _LIST_NODE {
    int data;
    LIST_NODE *next; // CORRECT, with Forward decl.
};


LIST_NODE *reverse_list(LIST_NODE *head) {
    LIST_NODE *node_current, *node_prev, *node_next = NULL;
    
    if(head == NULL) 
        return NULL;
    // end of list is marked with NULL;
    for(node_prev = NULL, node_current = head, node_next = NULL; node_current != NULL; node_current = node_next) {
        //node_current->next;
        node_next = node_current->next;
        node_current->next = node_prev;
        node_prev = node_current;
        //node->next = node_prev;
        
    }
    
    return node_prev;

}
static void print_list(LIST_NODE *head) {
    LIST_NODE *node;

    if(head == NULL) {
        printf("EMPTY LIST\n");
        return;
    }

    for(node = head; node != NULL && node->next != NULL; node = node->next) {
        printf("%d->", node->data);
    }

    printf("%d->NULL\n", node->data);

    return;
}

LIST_NODE test_list0[] = {{7, NULL}, {5,NULL}, {3, NULL} };
int main(void) {
    int i;
    LIST_NODE *list0 = NULL;
    LIST_NODE *revlist = NULL;

    for(i = 0; i < sizeof(test_list0)/sizeof(test_list0[0]) - 1; i++) {
        test_list0[i].next = &test_list0[i+1];
    }

    list0 = test_list0;

    print_list(list0);

    revlist = reverse_list(list0);

    print_list(revlist);
    return 0;
}