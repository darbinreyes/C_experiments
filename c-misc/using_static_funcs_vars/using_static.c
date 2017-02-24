/**

Can I still call a function that I defined as static but expose
non-static headers?

notes, simply declaring an external function at the top of the main file
does not make it visible to this module. This will only work if you tell the
compiler the name of the file that has the function definition when you compile
i.e.  cc using_static.c  my_static_funcs.c

In my_static_funcs.c you still need to #include <stdio.h> for the printf funcs
to be recognized by the compiler.

So declaring the functions at the top of the main file+compiling with
both the main file and the helper .c file makes the compiler+linker happy.

So the function signature tells the compiler this function is defined, but not
in this file. The compiler will search for the definition in the standard places
+other files you passed in the command line.

making the helper function static hides it even with a decl of the function header
at the top of the file , even if you make it static at the top of a header
that is included.


**/


#include <stdio.h>

#include "my_static_funcs.h"

int
main (
  void
  ) {

  printf("hello world.\n");
  func1();
  func_xyz ();
  return 0;

}