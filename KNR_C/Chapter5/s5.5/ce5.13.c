#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define DEFAULT_TAIL 10

#define MAXLINES    5000
#define MAXLINESIZE 256

// used by read lines
// from  /Users/darbinreyes/dev/experiments/C/KNR_C/Chapter5/s5.5/ce5.6.c
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
void writelines_tail(char *lines[], int len, int tail) {

  assert(lines != NULL);
  int i = 0;

  while(len > 0) {
    if(len-- <= tail)
      printf("%s", *lines);

    free(*lines++);
  }

}


void errmsg(void){
  printf("Usage: tail -n. n is an positive integer. Default is 10.\n");
}

int main(int argc, char *argv[]){
  int tailn = DEFAULT_TAIL;
  char *lines[MAXLINES];
  int numlines;

  if(argc > 2)
    errmsg();

  //get tail n from argv.
  if(argc == 2) {
    if(**++argv == '-') {
      //printf("argc = %d, argv = %s\n",argc, *argv);

      tailn = atoi(++*argv); //atoi(((*argv)++)); // parens on ++ does not force it to happen before the atoi() call

      if(tailn <= 0){
        errmsg();
        return 1;
      }
    }
  }

  if(tailn <= 0){
    errmsg();
    return 1;
  }

  // read all lines.
  numlines = readlines(lines, sizeof(lines)/ sizeof(*lines));

  // print last n lines
  writelines_tail(lines, numlines, tailn);

  //free lines
  return 0;
}