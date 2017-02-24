#include <stdio.h>

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

void insert_spaces(int num) {
  while(num-- > 0)
      putc(' ', stdout);

}

void insert_tab(int num) {
  while(num-- > 0)
      putc('\t', stdout);

}

void insert_tab_stop(int col, int m, int n, int num, void (*insert_tabstop)(int num)) {
    if(n < 0 || m < 0)
      return;

    if((col >= m) && (col % n) == 0)
        insert_tabstop(num);

}

void insert_tab_stop_list(int col, int *stops, int len, int num, void (*insert_tabstop)(int num)) {

  while(len-- > 0)
    if(*stops++ == col)
      insert_tabstop(num);

}