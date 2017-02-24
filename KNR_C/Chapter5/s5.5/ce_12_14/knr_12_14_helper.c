#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAXLINESIZE 256

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
       return -1;
    else if (v1 > v2)
       return 1;
    else
        return 0;
}


void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];

    v[i] = v[j];

    v[j] = temp;
}

size_t my_getline(char *s,const int lim)
{
  char c;
  char *t;
  t=s;
  assert(lim != 0);
  while(s < (s+lim-1) && (c=getchar()) != EOF && c!='\n')
    *s++ = c;

  if(c == '\n')
    *s++ = c;

  *s = '\0';
  return (size_t)(s-t+1);
}

int readlines(char *lines[], int maxlines){
  int count = 0, linesize = 0;
  char line[MAXLINESIZE];

  while( ( linesize = my_getline(line, sizeof(line)) ) > 1 && count < maxlines ){
    lines[count] = malloc(linesize*sizeof(char));

    if(lines[count] == NULL) {
      printf("Out of mem. number of lines read = %d.\n", count);
      break;
    }

    strcpy(lines[count], line);
    count++;
  }

  return count;
}

// output lines
void writelines(char *lines[], int len) {

  assert(lines != NULL);

  while(len-- > 0) {
    printf("%s", *lines);
    free(*lines++);
  }

}