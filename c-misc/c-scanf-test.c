#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxlines   1000
#define maxstrsize 22

char nlines[maxlines][maxstrsize];
char qlines[maxlines][maxstrsize];

void getAllLines(char lines[maxlines][maxstrsize], int count){
    int i = 0;
    size_t linesize = 0;
    char *line = NULL;
    
    printf("count = %d.\n", count);

    for(i = 0; i < count; i++){
        fgets(&lines[i][0], maxstrsize, stdin);
        if(lines[i][strlen(lines[i])-1] == '\n')
            lines[i][strlen(lines[i])-1] = '\0';
        printf("%d : %s.\n", i, lines[i]);
    }
}

int countstr(char lines[maxlines][maxstrsize], int N, char *qstr){
    int i = 0;
    int count = 0;
    
    for(i = 0; i < N; i++)
        if(!strcmp(&lines[i][0], qstr))
            count++;

        return count;
}
int main() {
    int N, Q, i;
    
    scanf("%d\n", &N);
    getAllLines(nlines, N);
    scanf("%d\n", &Q);
    getAllLines(qlines, Q);
    
    for(i = 0; i < Q; i++)
        printf("%d\n", countstr(nlines, N, &qlines[i][0]));
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
