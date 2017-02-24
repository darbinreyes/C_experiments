/**

C is consistent and regular in its approach to address arithmetic; its
integration of pointers, arrays, and address arithmetic is one of the strengths
of the language. Let us illustrate by writing a rudimentary storage allocator.
There are two routines.

The first, alloc(n), returns a pointer to n consecutive
character positions, which can be used by the caller of alloc for storing
characters.


The second, afree(p), releases the storage thus acquired so it can
be re- used later.

The routines are ``rudimentary'' because the calls to afree
must be made in the opposite order to the calls made on alloc. That is, the
storage managed by alloc and afree is a stack, or last-in, first-out.

The standard library provides analogous functions called malloc and free that have
no such restrictions; in Section 8.7 we will show how they can be implemented.

**/

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position. This could also have been written static char *allocp = &allocbuf[0]; */

char *alloc(int n) /* return pointer to n characters */
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */

    /**
      allocbuf + ALLOCSIZE = 1 more than the address of the last char in the buffer.
      allocbuf + ALLOCSIZE - allocp = how many free chars we have left.
      So this test tells us if we have n or more chars left in buffer to return.
    **/

    allocp += n;
    return allocp - n; /* old p */
  } else /* not enough room */
    return 0;
}


void afree(char *p) /* free storage pointed to by p */
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}