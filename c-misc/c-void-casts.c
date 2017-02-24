#include <stdio.h>

// We know we don't need explicit cast to void *, but what about from void * to another pointer?
void foo(int *p){
  printf("No problem - cc did not complain about passing void * to foo(int *p)\n");
}

void bar(void *p) {

}
int main(void){
 int i = 0;
 void *vp = 0;

 // to void *, of course this is ok.
 bar(&i);

 // from void * ? - Yup OK with cc. Probably depends on compiler flags though.
 foo(vp);

}