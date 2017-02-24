#include <stdio.h>
#include <stdlib.h>

int update_line_col(char c);
void insert_spaces(int num);
void insert_tab(int num);
void insert_tab_stop(int col, int m, int n, int num,  void (*insert_tabstop)(int num));

int get_m_n(int argc,char **argv, int *m, int *n);
int get_tab_stops(int *tabstops, int maxstops, int argc, char *argv[]);
void insert_tab_stop_list(int col, int *stops, int len, int num, void (*insert_tabstop)(int num));


#define MAX_TABS_STOPS 80
#define NUMSPACES 4

void detab(int m, int n, int *stops, int stopslen) {
    int c;
    const int tabsize = NUMSPACES;
    int count = 0;
    int col = 0;

    while((c = getc(stdin)) != EOF) {

      col = update_line_col(c);
      insert_tab_stop(col, m, n, tabsize, insert_spaces);
      insert_tab_stop_list(col, stops, stopslen, tabsize, insert_spaces);

      if(c == '\t') {
          count++;
      }
      else {
          insert_spaces(count*tabsize);

          putc(c, stdout);
          count = 0;
      }

    }
}

int main(int argc,char **argv) {
    int m, n;
    int tabstops[MAX_TABS_STOPS];
    int lenstops = 0;

    if(!get_m_n(argc, argv, &m, &n)) {
        detab(m, n, tabstops, lenstops);
    } else {
        lenstops = get_tab_stops(tabstops, MAX_TABS_STOPS, argc, argv);
        detab(m, n, tabstops, lenstops);
    }


  //printf("m = %d. n = %d\n", m, n);
}