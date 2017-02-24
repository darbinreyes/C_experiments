#include <stdio.h>
#include "stack.h"

// formal pda definition

typedef enum {
    q0=0,
    q1=1,
    q2=2,
    qerror = 3
} PDA_STATE;

typedef enum {
    t0='0',
    t1='1',
    t2='c',
} PDA_TERMINAL;

typedef enum {
    v0='Z'
} PDA_VARIABLE;

typedef enum {
    s0=t0,
    s1=t1,
    s2=t2,
    s3=v0
} PDA_STACK_SYMBOL;

typedef struct {
    PDA_TERMINAL     t;
    PDA_STACK_SYMBOL v;
    PDA_STACK_SYMBOL nextstack[3];
} TABLE_ENTRY;

// push whatevers on the input
TABLE_ENTRY q0q0table[] = {
{'0','Z',{'0','Z','\0'}},
{'1','Z',{'1','Z','\0'}},
{'0','0',{'0','0','\0'}},
{'0','1',{'0','1','\0'}},
{'1','0',{'1','0','\0'}},
{'1','0',{'1','1','\0'}}
};

// move past center marker
TABLE_ENTRY q0q1table[] = {
{'c','Z',{'Z','\0'}},
{'c','0',{'0','\0'}},
{'c','1',{'1','\0'}}
};

// pop matching input with stack top.
TABLE_ENTRY q1q1table[] = {
{'0','0',{'\0','\0'}},
{'1','1',{'\0','\0'}}
};
// until theres no more input , at which point Z should be exposed.
TABLE_ENTRY q1q2table[] = {
{'\0','Z',{'Z','\0'}}
};

TABLE_ENTRY *
FindEntry(TABLE_ENTRY *table, int len, int input, int top) {
    for(int i = 0; i < len; i++){
        if(table[i].t == input && table[i].v == top){
            return &table[i];
        }
    }

    return NULL;
}

void
UpdateStack(PDA_STACK_SYMBOL *nextstack) {
    int i;

    if(!isEmpty()) {
      printf("UpdateStack pop(%c).\n", pop());
    } else {
      printf("UpdateStack stack is empty.\n");
    }

    for(i = 0; nextstack[i] != '\0'; i++)
      ;

    for(; i > 0 ; i--){
        printf("UpdateStack push(%c).\n", nextstack[i-1]);
        push(nextstack[i-1]);
    }
}

int
TransitionFunction(int state, int input, int top) {
  TABLE_ENTRY *entry;

  printf("TransitionFunction state = %d, input = %c, top = %c.\n", state, input, top);

  if(state == q0){
    if((entry = FindEntry(q0q0table, sizeof(q0q0table)/sizeof(TABLE_ENTRY), input, top))){
        UpdateStack(entry->nextstack);
        return q0;
    }

    if((entry = FindEntry(q0q1table, sizeof(q0q1table)/sizeof(TABLE_ENTRY), input, top))){
        UpdateStack(entry->nextstack);
        return q1;
    }

    return qerror;
  }

  if(state == q1){

    if((entry = FindEntry(q1q1table, sizeof(q1q1table)/sizeof(TABLE_ENTRY), input, top))){
        UpdateStack(entry->nextstack);
        return q1;
    }

    if((entry = FindEntry(q1q2table, sizeof(q1q2table)/sizeof(TABLE_ENTRY), input, top))){
        UpdateStack(entry->nextstack);
        return q2;
    }

    return qerror;
  }

  if(state == q2) {
      return qerror;
  }

  return qerror;
}
int
main(void) {
    PDA_STATE state;
    char input;
    int inputconsumed;

    // init state
    state = q0;
    push('Z');

    while((input = getchar()) != EOF && input != '\n'){
        state = TransitionFunction(state, input, peek());

        if(state == q2){
            printf("Final state reached.\n");
            break;
        }

        if(state == qerror){
            printf("Error state reached.\n");
            break;
        }
    }

    inputconsumed = input == '\n' || input == EOF;

    if(inputconsumed)
      state = TransitionFunction(state, '\0', peek());

    if(!isEmpty())
      printf("main state = %d, input consumed = %d, top = %c.\n", state, inputconsumed, peek());
    else
      printf("main state = %d, input consumed = %d, isempty = %d.\n", state, inputconsumed, isEmpty());

    if(state == q2){
      printf("Input accepted by PDA.\n");
    } else {
      printf("Input rejected.\n");
    }
    return 0;
}