/*
Exercise 1-19. Write a function reverse(s) that reverses the character string s.
 Use it to write a program that reverses its input a line at a time.

*/
#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int my_getline(char s[],int lim);
void my_reverse(char *s);

int main(void) {
    char line[MAXLINE];
    int  len;

    while((len = my_getline(line, MAXLINE)) > 0){
        //remove the new line so we don't reverse it. 
        line[len-1] = '\0';
        my_reverse(line);
        printf("%s\n", line);
    }

    return 0;
}

/* getline: read a line into s, return length */
// modified to ensure we always append a new line char. 
int my_getline(char s[],int lim)
{
    int c, i;
    for (i=0; i < lim-2 && (c=getchar())!=EOF && c!='\n'; ++i) 
        s[i] = c;
    
    if(c != EOF)
        s[i++] = '\n'; 
    
    s[i] = '\0';
    return i; 
}

// reverse the string s
void my_reverse(char *s){
    char *e;
    char tmp;

    if(*s == '\0') // nothing to do.
        return;

    e = s;
    // find the end of the string. 
    while(*(e+1) != '\0')
        e++;

    while(s < e){
        tmp = *e;
        *e = *s;
        *s = tmp;
        s++;
        e--;
    }

}

