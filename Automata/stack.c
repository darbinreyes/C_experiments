#include <assert.h>

#define STACK_LENGTH_MAX 100

static int stack[STACK_LENGTH_MAX];
static int *top = stack; // points to next empty slot at top of stack.

int
isFull(void){
  return top > &stack[STACK_LENGTH_MAX];
}
void
push(int n){
  assert(!isFull());
  *top++ = n;
}

int
isEmpty(void){
  return top == stack;
}

int
pop(void){

  assert(!isEmpty());

  return *--top;
}

int
peek(void){

  assert(!isEmpty());

  return *(top-1);
}