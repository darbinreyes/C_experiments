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

void entab(int m, int n, int *stops, int stopslen) {
    int c;
    const int tabsize = NUMSPACES;
    int spacecount = 0;
    int col = 0;

    while((c = getc(stdin)) != EOF) {

      col = update_line_col(c);
      insert_tab_stop(col, m, n, 1, insert_tab);
      insert_tab_stop_list(col, stops, stopslen, 1, insert_tab);

      if(c == ' ') {
          spacecount++;
      }
      else {
          insert_tab(spacecount/tabsize);
          insert_spaces(spacecount%tabsize);

          putc(c, stdout);
          spacecount = 0;
      }

    }
}

int main(int argc,char **argv) {
    int m, n;
    int tabstops[MAX_TABS_STOPS];
    int lenstops = 0;

    if(!get_m_n(argc, argv, &m, &n)) {
        entab(m, n, tabstops, lenstops);
    } else {
        lenstops = get_tab_stops(tabstops, MAX_TABS_STOPS, argc, argv);
        entab(m, n, tabstops, lenstops);
    }


  //printf("m = %d. n = %d\n", m, n);
}