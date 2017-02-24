#include <stdio.h>

int nextstate(int state, char c);

#define IN   1 // currently inside a comment
#define OUT  0 // outside a comment. 

/*
From K&R 4.3 External Variables - On ungetch()

What are getch and ungetch? It is often the case that a program cannot determine that it has read enough input until it has read too much. One instance is collecting characters that make up a number: until the first non-digit is seen, the number is not complete. But then the program has read one character too far, a character that it is not prepared for.
The problem would be solved if it were possible to ``un-read'' the unwanted character. Then, every time the program reads one character too many, it could push it back on the input, so the rest of the code could behave as if it had never been read. Fortunately, it's easy to simulate un- getting a character, by writing a pair of cooperating functions. getch delivers the next input character to be considered; ungetch will return them before reading new input.
How they work together is simple. ungetch puts the pushed-back characters into a shared buffer -- a character array. getch reads from the buffer if there is anything else, and calls getchar if the buffer is empty. There must also be an index variable that records the position of the current character in the buffer.
Since the buffer and the index are shared by getch and ungetch and must retain their values between calls, they must be external to both routines. Thus we can write getch, ungetch, and their shared variables as:

7.8.3 Ungetc
The standard library provides a rather restricted version of the function ungetch that we wrote in Chapter 4; it is called ungetc.
int ungetc(int c, FILE *fp)
pushes the character c back onto file fp, and returns either c, or EOF for an error. Only one character of pushback is guaranteed per file. ungetc may be used with any of the input functions like scanf, getc, or getchar.
*/
int main(void) {
    int state, c, c_prev, inout;

    state = 0;
    inout = OUT; // For handling '/' chars that occur in arithmetic expressions. 
    while((c = getchar()) != EOF){
        state = nextstate(state, (char)c);

        if(state >= 1 && state <= 7){ // we are inside a C comment, don't output anything.
            inout = IN;
            c_prev = c;

            if(state == 3)
                putchar('\n'); // output a new line once we match a in line comment to prevent unwanted line merging. 

            if(state == 3 || state == 7) {
                state = 0; // matched a comment, reset the automaton
                inout = OUT;
            }
        } else { //  outside a comment, echo the input.
            if(inout == IN){
                inout = OUT; 
                putchar(c_prev); // pushback the previous char, we started but did not reach a path to a final state.
            }
            putchar(c);
        }
    }

    return 0;
}

int getinputid(char c){
    int input;

   switch(c){
    case '/':
        input = 0;
        break; 
    case '\n':
        input = 1;
        break;
    case '\\':
        input = 2;
        break;
    case '*':
        input = 3;
        break;
    case '"':
        input = 4;
        break;
    case '\'':
        input = 5;
        break;
    default:
        input = 6;
        break;   
    }

    return input;
}

int nextstate(int state, char c){
    // assert(state >=0 && state <=11)
    // the transition table for the Automaton that will be used for removing comments from a *valid* C program.
/*
READ THIS YOU FUCKING FUCK, THIS SHIT SHOULD BE EASY!:

    ce1.23.c:44:24: error: array has incomplete element type 'const int []'
    static const int tt[][] = { \
                       ^
    1 error generated.
From K&R 5.7, Multi-dimensional arrays. 

If a two-dimensional array is to be passed to a function, the parameter 
declaration in the function must include the number of COLUMNS; the number of 
rows is irrelevant, since what is passed is, as before, a pointer to an array 
of rows, where each row is an array of 13 ints. In this particular case, it is 
a pointer to objects that are arrays of 13 ints. 
*/
    static const int tt[][7] = { \
        {1 ,0 ,0 ,0 ,8 ,10,0},
        {2 ,0 ,0 ,5 ,0 ,0 ,0},
        {2 ,3 ,4 ,2 ,2 ,2 ,2},
        {0 ,0 ,0 ,0 ,0 ,0 ,0},
        {2 ,2 ,2 ,2 ,2 ,2 ,2},
        {5 ,5 ,5 ,6 ,5 ,5 ,5},
        {7 ,5 ,5 ,5 ,5 ,5 ,5},
        {0 ,0 ,0 ,0 ,0 ,0 ,0},
        {8 ,8 ,9 ,8 ,0 ,8 ,8},
        {8 ,8 ,8 ,8 ,8 ,8 ,8},
        {10,10,11,10,10,0 ,10},
        {10,10,10,10,10,10,10}
    };

    int input = getinputid(c);

    return tt[state][input];
}


