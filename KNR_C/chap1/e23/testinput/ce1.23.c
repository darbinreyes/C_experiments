#include <stdio.h>

int nextstate(int state, char c);

int main(void) {
    int state, c;

    state = 0;
    while((c = getchar()) != EOF){
        state = nextstate(state, (char)c);

        if(state >= 1 && state <= 7){ // we are inside a C comment, don't output anything.
            if(state == 3)
                putchar('\n'); // output a new line once we match a in line comment to prevent unwanted line merging. 
            if(state == 3 || state == 7)
                state = 0; // matched a comment, reset the automaton
        } else { //  outside a comment, echo the input.
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
        {10,10,10,10,11,10,10}
    };

    int input = getinputid(c);

    return tt[state][input];
}


