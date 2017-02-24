#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// infix, (1 - 2) * (4 + 5)
// postfix 1 2 - 4 5 + *
#include <curses.h>

enum {
  NUM = '0',
  ADD = '+',
  SUB = '-',
  MULT = '*',
  DIV = '/',
  ERRR = -1
};

#define STACKSIZE 64

double stack[STACKSIZE];
double *top = stack;

void push(double i) {
  if(top < stack + STACKSIZE)
    *top++ = i;
  else {
    printf("Error: Stack is full!");
  }
}

double pop(void) {
  if(top > stack)
    return *--top;
  else {
    printf("Error: Stack is empty!");
  }
  return 0;
}
#if 0
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
#endif

void collectnum(char *s) {
  int c;

  s++;

  while(isdigit(c=getchar()))
    *s++ = (char)c;

  if(c == '.') {
    *s++ = (char)c;
    while(isdigit(c=getchar()))
      *s++ = (char)c;
  }

  ungetc(c, stdin);
  //putc(c,stdin);
  *s = '\0';

}

#define NUM '0'

int getop(char *s) {
  int c, type;

  while(isspace(c=getchar()))
    ;

  if(isdigit(c)) {
    *s = c;
    collectnum(s);
    printf("Error: s = %s.\n", s);
    return NUM;
  }

  if(c == '+' || c == '-' || c == '*' || c == '/')
    return c;

  return -1;
}


double eval(void) {
  char s[100];
  int op1, op2, t;
  while((t = getop(s)) != ERRR)
    switch(t) {
      case ERRR:
        printf("Error: bad input.");
        break;
      case NUM:
        push(atof(s));
        break;
      case SUB:
        op2 = pop();
        push(pop() - op2);
        break;
      case ADD:
        push(pop() + pop());
        break;
      case MULT:
        push(pop() * pop());
        break;
      case DIV:
        op2 = pop();
        if(op2 != 0)
          push(pop() / op2);
        else
          printf("Error: Div by 0.");
        break;
    }

  return pop();
}


/** Tests via command line since getchar() uses stdin.

Darbin-Reyess-MacBook-Pro:s5.5 darbinreyes$ echo '1 2 +' | ./a.out
Error: s = 1.
Error: s = 2.
eval = 3.000000
Darbin-Reyess-MacBook-Pro:s5.5 darbinreyes$ echo '1 2 - 4 5 + *' | ./a.out
Error: s = 1.
Error: s = 2.
Error: s = 4.
Error: s = 5.
eval = -9.000000
Darbin-Reyess-MacBook-Pro:s5.5 darbinreyes$

**/
int main(void) {
 // char s[] = "1 2 - 4 5 + *";
  printf("eval = %f\n", eval());
  //test_eval1();
}