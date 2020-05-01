#include <stdio.h>
// Exercise 1-14. Write a program to print a histogram of the frequencies of different characters in its input.


void char_freq_counter(void){
    // get each char from stdin one at a time. 
    // count any chars from ascii value c=' ', to '~'.
    // use an array to store the count for each char, where index = 0 , is the 
    // count for ' '.
#define UPPER_CHAR '~'
#define LOWER_CHAR ' '
    unsigned long charfreq[UPPER_CHAR - LOWER_CHAR + 1] = {0};
    int c;

    while((c = getchar()) != EOF){
        if(c >= LOWER_CHAR && c <= UPPER_CHAR)
            charfreq[c - LOWER_CHAR]++;
    }

    c = 0;

    while(c < sizeof(charfreq)/sizeof(unsigned long)) {
        /*
            Whether or not a variable of type char is signed or unsigned 
            in expressions is machine dependent. Therefore, to ensure correct 
            interpretation use casts. 
        */
        printf("%c: %lu\n", (char)((char)c+(char)LOWER_CHAR),charfreq[c]);
        c++;
    }
}

/*
Exercise 1-16. Revise the main routine of the longest-line program so it will 
correctly print the length of arbitrary long input lines, and as much as possible of the text.
*/


#define MAXLINE 1000 /* maximum input line length */

int mygetline(char line[], int maxline); 
int mygetline_1_16(char line[], int maxline); 
void copy(char to[], char from[]);
/* print the longest input line */

int main_1_16(void)
{
    /*current line length */ 
    /* maximum length seen so far */ 
    /* current input line */
    /* longest line saved here */
    int len;
    int max;
    char line[MAXLINE]; 
    char longest[MAXLINE];

    max = 0;

    while ((len = mygetline_1_16(line, MAXLINE)) > 0)
        if (len > max) { 
            max = len;
            copy(longest, line); 
        }
    
    if(max > 0) /*therewasaline*/ 
        printf("%s", longest);
    
    return 0; 
}

/*
Exercise 1-17. Write a program to print all input lines that are longer than 80 characters. 
*/
int main_1_17(void)
{
    /*current line length */ 
    /* maximum length seen so far */ 
    /* current input line */
    /* longest line saved here */
    int len;
    char line[MAXLINE]; 


    while ((len = mygetline_1_16(line, MAXLINE)) > 0)
        if (len > 80) { 
            printf("%s", line);
        }
        
    return 0; 
}

/* mygetline: read a line into s, return length */
int mygetline(char s[],int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) 
        s[i] = c;
    
    if (c == '\n') { 
        s[i] = c;
        ++i; 
    }
    
    s[i] = '\0';
    return i; 
}

int mygetline_1_16(char s[],int lim)
{
    int c, i, j;

    /*
        copy only lim-1 chars, 
    */
    for (i=0, j=0; (c=getchar())!=EOF && c!='\n'; ++i) 
        if(j < lim-1)
            s[j++] = c;
    
    if (c == '\n' && j < lim-1) { 
        s[j] = c;
        ++j; 
        ++i;// count the \n char
    }
    
    s[j] = '\0';
    return i; 
}
/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;
    i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i; 
}









int main(void){
    //char_freq_counter();
    //main_1_16();
    main_1_17();
}