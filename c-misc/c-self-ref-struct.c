#include <stdio.h>

int 
main(void){
	struct my_struct {
		int num;
		struct my_struct *next_ms;
	} ms, ms2;

	ms.num = 2;
	ms2.num = 3;
	ms.next_ms = &ms2;
	printf("hi buddy. %d, %d.\n", ms.num, ms.next_ms->num);
}