#include <stdio.h>
#include <assert.h>
#include <ctype.h>

int casei_strcmp(const char *s1, const char *s2) {
    int cmp = 0;
    assert(s1 != NULL && s2 != NULL);

    while(cmp == 0) {
        if(isalpha(*s1) && isalpha(*s2))
            cmp = tolower(*s1) - tolower(*s2);
        else
            cmp = *s1 - *s2;

        if(*s1 == '\0' || *s2 == '\0')
            break;
        s1++;
        s2++;
    }

    return cmp;
}

int dir_strcmp(const char *s1, const char *s2) {
    int cmp = 0;
    int s1cmp;
    int s2cmp;
    assert(s1 != NULL && s2 != NULL);
    printf("dircmp: %s %s.\n", s1, s2);

    while(cmp == 0) {

        s1cmp = isalnum(*s1) || isblank(*s1);
        s2cmp = isalnum(*s2) || isblank(*s2);

        if(s1cmp && s2cmp) {
            cmp = *s1 - *s2;
            s1++;
            s2++;
        }
        else if(s1cmp && !s2cmp) {
            s2++;
        }
        else if(!s1cmp && s2cmp) {
            s1++;
        } else {
            s1++;
            s2++;
        }

        if(*s1 == '\0' || *s2 == '\0')
            break;
    }

    printf("dircmp == %d.\n", cmp);

    return cmp;
}

int dirf_strcmp(const char *s1, const char *s2) {
    int cmp = 0;
    int s1cmp;
    int s2cmp;
    assert(s1 != NULL && s2 != NULL);
    printf("dircmp: %s %s.\n", s1, s2);

    while(cmp == 0) {

        s1cmp = isalnum(*s1) || isblank(*s1);
        s2cmp = isalnum(*s2) || isblank(*s2);

        if(s1cmp && s2cmp) {
            cmp = tolower(*s1) - tolower(*s2);
            s1++;
            s2++;
        }
        else if(s1cmp && !s2cmp) {
            s2++;
        }
        else if(!s1cmp && s2cmp) {
            s1++;
        } else {
            s1++;
            s2++;
        }

        if(*s1 == '\0' || *s2 == '\0')
            break;
    }

    printf("dircmp == %d.\n", cmp);

    return cmp;
}