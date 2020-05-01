#include <stdio.h>



void char_freq_counter(void){
    
    
    
    
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
        
        printf("%c: %lu\n", (char)((char)c+(char)LOWER_CHAR),charfreq[c]);
        c++;
    }
}




#define MAXLINE 1000 

int mygetline(char line[], int maxline); 
int mygetline_1_16(char line[], int maxline); 
void copy(char to[], char from[]);


int main_1_16(void)
{
     
     
    
    
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
    
    if(max > 0)  
        printf("%s", longest);
    
    return 0; 
}


int main_1_17(void)
{
     
     
    
    
    int len;
    char line[MAXLINE]; 


    while ((len = mygetline_1_16(line, MAXLINE)) > 0)
        if (len > 80) { 
            printf("%s", line);
        }
        
    return 0; 
}


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

    
    for (i=0, j=0; (c=getchar())!=EOF && c!='\n'; ++i) 
        if(j < lim-1)
            s[j++] = c;
    
    if (c == '\n' && j < lim-1) { 
        s[j] = c;
        ++j; 
        ++i;
    }
    
    s[j] = '\0';
    return i; 
}

void copy(char to[], char from[])
{
    int i;
    i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i; 
}









int main(void){
    
    
    main_1_17();
}