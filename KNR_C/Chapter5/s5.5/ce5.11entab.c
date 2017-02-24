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

void insert_tab_stop(int col, int *stops, int len) {

  while(len-- > 0)
    if(*stops++ == col)
      putc('\t', stdout);

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

int main(int argc, char *argv[]) {
    int c;
    int tabsize = NUMSPACES;
    int spacecount = 0;
    int i, col = 0;
    int tabstops[MAX_TABS_STOPS];
    int lenstops;

  lenstops = get_tab_stops(tabstops, MAX_TABS_STOPS, argc, argv);
  //for(i = 0; i < lenstops; i++)
  //  printf("%d\n", tabstops[i]);
  // entab
  while((c = getc(stdin)) != EOF) {

      col = update_line_col(c);
      insert_tab_stop(col, tabstops, lenstops);

      if(c == ' ') {

          // replace tabsize adjacent spaces with a tab
          spacecount++;
          while ((c = getc(stdin)) == ' ') {

              col = update_line_col(c);
              insert_tab_stop(col, tabstops, lenstops);

              spacecount++;

              if(spacecount % tabsize == 0) {
                putc('\t', stdout);
                spacecount = 0;
              }
          }

          col = update_line_col(c);
          insert_tab_stop(col, tabstops, lenstops);

          // if we hit a tab output it first
          if(c == '\t')
            putc(c, stdout);

          // then output trailing spaces.
          while(spacecount-- > 0)
              putc(' ', stdout);

          if(c != '\t')
            putc(c, stdout);
      }
      else {
        putc(c, stdout);
        spacecount = 0;
      }

  }

}