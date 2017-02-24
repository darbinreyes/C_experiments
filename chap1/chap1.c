
#include <stdio.h>

void fartocel_1_3(void);
void celtofar_1_4(void);
void reverse_fartocel_1_5(void);
void test_getchar_expression_1_6(void);
void ws_counter_1_8(void);
void multi_blanks_remover_1_9(void);
void escape_t_bsp_bsl_1_10(void);
void print1wperline_1_12(void);
void wordlens_histogram(void);

int main(void) {
    //fartocel_1_3();
    //celtofar_1_4();
    //reverse_fartocel_1_5();
    //test_getchar_expression_1_6();
    //ws_counter_1_8();
    //multi_blanks_remover_1_9();
    //escape_t_bsp_bsl_1_10();
    //print1wperline_1_12();
    wordlens_histogram();

    return 0;
}

void fartocel_1_3(void){
    float fahr, celsius; float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    /* lower limit of temperature scale */ /* upper limit */
    /* step size */
    fahr = lower;
    printf("|%-3s |%-6s|\n", "F", "C");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0); 
        printf("|%3.0f |%6.1f|\n", fahr, celsius);
        fahr = fahr + step;
    }
}

void celtofar_1_4(void) {
    float fahr, celsius; float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 10;
    /* lower limit of temperature scale */ /* upper limit */
    /* step size */
    //fahr = lower;
    celsius = lower;
    printf("|%-3s |%-6s|\n", "C", "F");
    while (celsius <= upper) {
        //celsius = (5.0/9.0) * (fahr-32.0);
        fahr = (9.0/5.0) * celsius + 32.0;
        printf("|%3.0f |%6.1f|\n", celsius, fahr);
        celsius = celsius + step;
    }
}

void reverse_fartocel_1_5(void){
    float fahr, celsius; float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = upper;
    printf("|%-3s |%-6s|\n", "F", "C");
    while (fahr >= lower) {
        celsius = (5.0/9.0) * (fahr-32.0); 
        printf("|%3.0f |%6.1f|\n", fahr, celsius);
        fahr = fahr - step;
    }
}

// Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1. 
// run it like this ./a.out <infile.txt 
// + Exercise 1-7. Write a program to print the value of EOF.
void test_getchar_expression_1_6(void) {
    int c;

    while(1) {
        printf("\n( getchar() != EOF ) == %d\n", (c = getchar()) != EOF); // expect ./a.out , "a\n" prints 1, ./a.out "\n" prints 0
        if(c == EOF) {
            printf("ex1.7 EOF = %d.\nDone.\n", c);
            break;
        }
        putchar(c);
    }
}   

//Exercise 1-8. Write a program to count blanks, tabs, and newlines.
//Exercise 1-9. Write a program to copy its input to its output, replacing each string of one or
//more blanks by a single blank.



void ws_counter_1_8(void) {
    struct my_char_count_record {
        int count;
        char c;
    } blanks = {0 , ' '}, tabs = {0, '\t'} , newlines = {0, '\n'};

    int c;

    while((c = getchar()) != EOF){
        if(c == blanks.c)
            blanks.count++;
        else if(c == tabs.c)
            tabs.count++;
        else if(c == newlines.c)
            newlines.count++;
    }

    printf("blanks = %d, tabs = %d, newlines = %d.\n", blanks.count, tabs.count, newlines.count);
}

void multi_blanks_remover_1_9(void) {
    int c;
    int wasblank = 0;

    while((c = getchar()) != EOF) {
        // print any non-blank chars as is then set wasblank = 0;
        // if c is a blank && wasblank != 1, print it, set wasblank = 1;
        if(c != ' ') {
            putchar(c);
            wasblank = 0;
        } else if(!wasblank) {
            putchar(c);
            wasblank = 1;
        }
    }
}

// Exercise 1-10. Write a program to copy its input to its output, 
// replacing each tab by \t, each backspace by \b, and each backslash by \\. 
// This makes tabs and backspaces visible in an unambiguous way.
void escape_t_bsp_bsl_1_10(void) {
    int c;
    /*
    To input a backspace from the keyboard type \b then press enter.
    ctrl+d sends an EOF from the keyboard. 
    */
    while((c = getchar()) != EOF) {
        // implement for tabs first, then generalize to backspace and backslash
        if(c == '\t') {
            putchar('\\');
            putchar('t');
        } else if(c == '\b') {
            putchar('\\');
            putchar('b');
        } else if(c == '\\') {
            putchar('\\');
            putchar('\\');
        } else {
            putchar(c);
        }
    }
}

//Exercise 1-11. How would you test the word count program? 
//What kinds of input are most likely to uncover bugs if there are any?

/*
How to test the world count program:
write a program to generate test input with known output.
*/


//Exercise 1-12. Write a program that prints its input one word per line.
#define IN_A_WORD  1
#define OUT_A_WORD 0

int isnonwordchar(char c){
    return (c == ' ' || c == '\t' || c == '\n');
}

void print1wperline_1_12(void) {
    // with the loose definition that a word is any sequence of characters that 
    // does not contain a blank, tab or newline. => ' ' , '\t', '\n'

    /*
     get first char, if non-ws init state to IN_A_WORD,else init. to out
     of a word. then, while there is still input, get next char,
     if is non-ws, print it, if non-ws and state=IN_A_WORD, we just
     finished printing a full word so putchar a new line, set state=OUT_A_WORD,
     keep going until we hit a non-ws, put char that non-ws ans set, 
     state=IN_A_WORD. 
    */

     int state, c;

     c = getchar();

     if(c == EOF) // nothing to process
        return;

     state = isnonwordchar((char)c)?  OUT_A_WORD : IN_A_WORD; // determine how to init. state.

     if(state == IN_A_WORD) {
        putchar(c);
     }

     while((c = getchar()) != EOF) {
        if(!isnonwordchar((char)c)) {
            // we are either in a word already or starting a word for the first
            // time.
            putchar(c);
            state = IN_A_WORD;
        } else {
            // non-word char. 
            if(state == IN_A_WORD) {
                putchar('\n');
                state = OUT_A_WORD;
            }
        }
     }
     
     putchar('\n'); // new line in case we only get a single char as input or input ends with a word and is not followed by non-ws. 
}

//Exercise 1-13. Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
//Exercise 1-14. Write a program to print a histogram of the frequencies of different characters in its input.
#define MAX_WORD_LEN 10

void update_wordlens(int len);
void print_wordlens(void);
void print_wordlens_horiz_hist(void);
void print_wordlens_vert_hist(void);

void wordlens_histogram(void) {
    // with the loose definition that a word is any sequence of characters that 
    // does not contain a blank, tab or newline. => ' ' , '\t', '\n'

    /*
     start with the print one word per line save the char count in an array,
     reset the the count each time we exit a word. 
    */

     int state, c, len = 0;

     c = getchar();

     if(c == EOF) // nothing to process
        return;

     state = isnonwordchar((char)c)?  OUT_A_WORD : IN_A_WORD; // determine how to init. state.

     if(state == IN_A_WORD) {
        len++;
     }

     while((c = getchar()) != EOF) {
        if(!isnonwordchar((char)c)) {
            // we are either in a word already or starting a word for the first
            // time.
            state = IN_A_WORD;
            len++;

        } else {
            // non-word char. 
            if(state == IN_A_WORD) { // in->out transition 
                state = OUT_A_WORD;
                update_wordlens(len);
                len = 0; // reset the count for the next word
            }
        }
     }

    // if the input ended with a word we need to update the count since we only update the count
    // on a transition out of a word. 

    if(state == IN_A_WORD) { // in->EOF transition 
        update_wordlens(len);
    }

    //print_wordlens();
    //print_wordlens_horiz_hist();
    print_wordlens_vert_hist();
}

static int wordlens[MAX_WORD_LEN+1]; // index = 0 is the count for words of len = 1, i = 38, len = 39, i=39 len>=40

void update_wordlens(int len) {
    //update the word len array.
    if(len > 0 && len <= MAX_WORD_LEN)
        wordlens[len-1]++;
    
    if(len > MAX_WORD_LEN)
        wordlens[MAX_WORD_LEN]++;
}

void print_wordlens(void) {
    int c = 0;
    while(c <= MAX_WORD_LEN) {
        printf("%4d: %4d\n", c+1, wordlens[c]);
        c++;
    }
}

void print_wordlens_horiz_hist(void) {
    int c = 0;

    // 1: 4####
    // 2: 3###
    while(c <= MAX_WORD_LEN) {
        printf("%4d: %4d", c+1, wordlens[c]);

        while(wordlens[c]-- > 0)
            putchar('#');

        putchar('\n');

        c++;
    }
}

void print_wordlens_vert_hist(void) {
    int i, done;

    /*
1  2
_____
4  3
#   #
#   #
#   #
#   

Plan:
1. print the header.
header
max len is 40 so "%2d "
then several line separators. ____
2. print the histogram bars. 
scan the entire array until all elements = 0;
print "# " if len still >0, else print "  "

    */
//print the header
    for(i = 1; i <= MAX_WORD_LEN+1; i++)
        printf("%-2d ", i);
    
    putchar('\n');

    for(i = 1; i <= MAX_WORD_LEN+1; i++)
        printf("___");

    putchar('\n');

    for(i = 0; i < MAX_WORD_LEN+1; i++)
        printf("%-2d ", wordlens[i]);
    
    putchar('\n');
//print the histogram
    done = 0;
    while(!done) {
        done = 1;        
        for(i = 0; i <= MAX_WORD_LEN; i++) {
            if(wordlens[i]-- > 0) { // print one row at a time
                printf("#  ");
                done = 0;
            } else {
                printf("   ");
            }
        }
        putchar('\n');
    }
}
