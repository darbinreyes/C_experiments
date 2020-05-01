#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// infix, (1 - 2) * (4 + 5)
// postfix 1 2 - 4 5 + *


enum {
  NUM,
  ADD,
  SUB,
  MULT,
  DIV,
  ERR
};

#define STACKSIZE 64

int stack[STACKSIZE];
int *top = stack;

void push(int i) {
  if(top < stack + STACKSIZE)
    *top++ = i;
  else {
    printf("Error: Stack is full!");
  }
}

int pop(void) {
  if(top > stack)
    return *--top;
  else {
    printf("Error: Stack is empty!");
  }
  return 0;
}

int getop(char *s) {

  if(isdigit(*s))
    return NUM;

  switch(*s) {
    case '-':
      return SUB;
    case '+':
      return ADD;
    case '*':
      return MULT;
    case '/':
      return DIV;
  }

  return ERR;
}


int eval(char *s) {
  int op1, op2;

  while(*s != '\0') {
    while(isspace(*s))
      s++;

    switch(getop(s)) {
      case ERR:
        printf("Error: bad input.");
        break;
      case NUM:
        push(atoi(s));
        while(isdigit(*s))
          s++;
        break;
      case SUB:
        op2 = pop();
        push(pop() - op2);
        s++;
        break;
      case ADD:
        push(pop() + pop());
        s++;
        break;
      case MULT:
        push(pop() * pop());
        s++;
        break;
      case DIV:
        op2 = pop();
        if(op2 != 0)
          push(pop() / op2);
        else
          printf("Error: Div by 0.");
        s++;
        break;
    }
  }
  return pop();
}


int main(void) {
  char s[] = "1 2 - 4 5 + *";
  printf("eval = %d\n", eval(s));
}