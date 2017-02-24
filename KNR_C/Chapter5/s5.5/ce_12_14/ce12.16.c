
#include <stdio.h>
#include <string.h>
// https://packagecontrol.io/packages/C%20Improved

#define MAXLINES 5000 /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *), int reverse);
int numcmp(const char *, const char *);
int casei_strcmp(const char *s1, const char *s2);
int dir_strcmp(const char *s1, const char *s2);
int dirf_strcmp(const char *s1, const char *s2);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int reverse = 0;
    int fold = 0;
    int dir_order = 0;
    int (*cmpfunc)(const char *, const char *);

    cmpfunc = strcmp; //default
    while(--argc > 0 && **++argv == '-') // pre inc argv and deref first char // check types in exp. //
        while(*(++*argv)) // deref to char pointer , inc, deref to char
            switch(**argv) {
                case 'n':
                numeric = 1;
                cmpfunc = numcmp;
                break;
                case 'r':
                reverse = 1; // can be combined with all other options
                break;
                case 'f':
                fold = 1;
                cmpfunc = casei_strcmp;
                break;
                case 'd':
                dir_order = 1;
                cmpfunc = dir_strcmp;
                break;
                default:
                printf("Illegal option %c.\n", **argv);
                return 1;
            }

    if(fold && dir_order)
        cmpfunc = dirf_strcmp;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        printf("nlines = %d.\n", nlines);
        qsort( (void**) lineptr, 0, nlines - 1, (int (*)(void*, void*))cmpfunc, reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }

}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right, int (*comp)(void *, void *), int reverse)
{
    int i, last;
    void swap(void *v[], int, int);
    int cmp;

    if (left >= right) /* do nothing if array contains */ /* fewer than two elements */
        return;

    swap(v, left, (left + right)/2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        cmp = comp(v[i], v[left]);
        if(!reverse) {
            if(cmp < 0)
                swap(v, ++last, i);
        } else {
            if(cmp > 0)
                swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort(v, left, last - 1, comp, reverse);
    qsort(v, last + 1, right, comp, reverse);
}