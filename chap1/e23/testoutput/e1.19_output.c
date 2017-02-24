
#include <stdio.h>

#define MAXLINE 1000 

int my_getline(char s[],int lim);
void my_reverse(char *s);

int main(void) {
    char line[MAXLINE];
    int  len;

    while((len = my_getline(line, MAXLINE)) > 0){
        
        line[len-1] = '\0';
        my_reverse(line);
        printf("%s\n", line);
    }

    return 0;
}



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


void my_reverse(char *s){
    char *e;
    char tmp;

    if(*s == '\0') 
        return;

    e = s;
    
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

