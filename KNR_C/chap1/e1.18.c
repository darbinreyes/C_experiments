/*
Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input, and
to delete entirely blank lines.

solution:

get a new line of input, 
starting from the last char,(before the null terminator. index=len-1),
if(line[index] == ' ' || line[index] == '\t')
    line[index]  = '\0'
    index--;

index++
line[index]='\n'


*/

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int knr_getline(char s[],int lim);

int main(void) {
    char line[MAXLINE];
    int  len, i;
    printf("Hello, World\n");

    while((len = knr_getline(line, MAXLINE)) > 0) {
        i = len - 2; // for now assume none of the input lines go over the limit so line[len] = null  and line[len-1] = '\n'
        while(i >= 0 && (line[i] == ' ' || line[i] == '\t') ) 
            line[i--] = '\n';
        //if i <= 0, this was an entirely blank line. otherwise the nested loop will stop when we hit the first non blank, so we set line[i+2] = '\0' 
        if(i > 0){
            line[i+2] = '\0';
            printf("%s", line); 
        }
    }



    return 0;
}

/* mygetline: read a line into s, return length */
int knr_getline(char s[],int lim)
{
    int c, i;
    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) 
        s[i] = c;
    
    if (c == '\n') { // if c == '\n', i < lim - 1
        s[i] = c;
        ++i; 
    }
    
    s[i] = '\0';
    return i; 
}

// return a line from input, in line, at most copy lim - 1  chars , the returned
// line will always be null terminated. If the input line is longer than lim -1
// the new line char will not be included. the returned len doesn't not count the
// null terminator so line[len] always == null
int my_getline(char *line, int lim){
    int c;
    int i = 0;

    while((c = getchar()) != EOF){
        if(c == '\n')
            break;

        if(i < lim - 1)
            line[i++] = (char) c;
        else
            break;
    }

    if(c == '\n' && i < lim - 1)
        line[i++] = c;

    line[i] = '\0'; 
    return i;
}