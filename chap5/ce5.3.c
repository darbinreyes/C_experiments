#include <stdio.h>

/* strcat: concatenate t to end of s; s must be big enough */ 
void strcat0(char s[], char t[])
{
	int i, j;
	i = j = 0;
	while (s[i] != '\0') /* find end of s */
	i++;
	while ((s[i++] = t[j++]) != '\0') /* copy t */
	; 
}

void strcat1(char *s, char *t)
{
	while (*s != '\0') /* find end of s */ // *(s++) != '\0' 
	  s++;

	while ((*s++ = *t++) != '\0') /* copy t */
	 ; 
}

int
main() {
	char s[100] = "hello, world";
	char t[]    = " and goodnight.";

	printf("%s\n", s);
	strcat1(s, t);
	printf("%s\n", s);
}