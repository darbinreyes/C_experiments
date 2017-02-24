#include <stdio.h>

// In C, we can't declare functions within a struct directly
typedef 
void * 
(*TREE_INTERFACE_GET_ROOT_DATA) (void);

typedef 
int    
(*TREE_INTERFACE_GET_HEIGHT) (void);

typedef 
int    
(*TREE_INTERFACE_GET_NUMBER_OF_NODES) (void);

typedef 
int    
(*TREE_INTERFACE_IS_EMPTY) (void);

typedef
void    
(*TREE_INTERFACE_CLEAR) (void);

struct t {
struct s *p;
};

struct s {
struct t *q; 
};

typedef struct my_tree_interface_t {
	// operations common to all tree types

	//void *getRootData();
	TREE_INTERFACE_GET_ROOT_DATA getRootData;

	//int   getHeight();
	//int   getNumberOfNodes();
	//int   isEmpty();
	//void  clear();
} my_tree_interface;

int main()
{
	printf("hello, world\n");
}