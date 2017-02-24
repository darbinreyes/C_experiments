#include <stdio.h>
#include <stdlib.h>

int update_line_col(char c) {
    static int row = 1, col = 0;

    // keep track of the row/col

    if(c != '\n') {
        col++;
    } else {
        col = 0;
        row++;
    }

    return col;
}

void insert_tab_stop(int col, int *stops, int len, int numspaces) {

  while(len-- > 0)
    if(*stops++ == col)
      while(numspaces-- > 0)
        putc(' ', stdout);
}

int get_tab_stops(int *tabstops, int maxstops, int argc, char *argv[]) {
  int len = 0;
  while(--argc > 0 && len++ < maxstops){
    *tabstops++ = atoi(*++argv);
  }

  return len;
}

#define MAX_TABS_STOPS 80
#define NUMSPACES 4

int main(int argc,char *argv[]) {
  int c;
  int numspaces = NUMSPACES;
  int tabstops[MAX_TABS_STOPS];
  int lenstops;
  int col;

  lenstops = get_tab_stops(tabstops, MAX_TABS_STOPS, argc, argv);

  // detab
  while((c = getc(stdin)) != EOF) {

    col = update_line_col(c);
    insert_tab_stop(col, tabstops, lenstops, numspaces);

    if(c != '\t') {
      putc(c, stdout);
    }
    else {
      while(numspaces-- > 0) {
        putc(' ', stdout);
      }
    }

    numspaces = NUMSPACES;
  }

}