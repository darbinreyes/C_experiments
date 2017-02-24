/**

Using C syntax (not C++), we need to setup an interface to be used like this:
MY_INTERFACE * mip;
MY_BAR bar;
int Status;
InitMyInterface(&mip);
Status = mip->foo(&bar);
Where:
MY_BAR is a typedef for a structure with two members, both of type int.
MY_FOO (not listed directly in the example code) is a typedef for a function pointer for a function the takes a pointer to a structure typedef MY_BAR and returns an int.
MY_INTERFACE is a typedef for a structure with one member, a function pointer of type MY_FOO.

Please provide all the function, structure and variable declarations to the best of your ability given the available information. If you feel that required information is lacking, note the information lacking (in a comment) and provide your own answer so that you can complete the exercise.
Hint, this syntax is used heavily in the UEFI specification.
Attach your answer as an .h file.

typedef struct _MY_BAR {
  INTN Member1;
  INTN Member2;
} MY_BAR;


typedef
INTN
(EFIAPI *MY_FOO)(
    IN MY_BAR *MyBar
    );

typedef struct _MY_INTERFACE {
  MY_FOO MyFoo;
} MY_INTERFACE;

**/

