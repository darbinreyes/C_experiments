#include <stdio.h>
#include <string.h>
#include <stddef.h> // wchar_t
#include <stdlib.h> //system() 

void str_constant_var(void);
void formating_prints(void);
void machine_dependent_sign_mod(void);
void sizeof_no_parens(void);
void escape_chars_and_constants(void);
void comment_in_expression(void);
void test_num_chunks_calc(void);
void test_wide_str_pointer_arithmetic(void);
char *
MkDirFromUri(
  char *Uri,
  char *LastNode
  );

int main (void) {

    //str_constant_var();
    //formating_prints();
    //machine_dependent_sign_mod();
    //sizeof_no_parens();
    //escape_chars_and_constants();
    //comment_in_expression();
    //test_num_chunks_calc();
    //test_wide_str_pointer_arithmetic();
    MkDirFromUri("/rest/v1/systems/1/bios/settings", NULL);
    return 0;
}

#define MY_STR_CONST_HELLO "hello"  

void str_constant_var(void) {
    char *a = "hello";
    char b[] = "hello";
    char c[] = MY_STR_CONST_HELLO;
    printf("a) %s world.\n", a);
    //a[0] = 'c'; // ERROR is Bus Error 10. 
    printf("yoyoma plays the %s.\n", a);

    printf("b) %s world.\n", b);
    b[0] = 'c'; // OK!
    printf("yoyoma plays the %s.\n", b);

    printf("c) %s world.\n", c);
    c[0] = 'c'; // OK 2! 
    printf("yoyoma plays the %s.\n", c);
}

#define MY_STR_FMT_STRING "HTTP status code = %3d"

void formating_prints(void) {

    printf("Print an int = %d\n",  100);
    printf("Print an int = %6d\n", 100); // 3 space pad before the 100. 
    printf("Print an int = %2d\n", 100); // This won't truncate the int. , %2d means use AT LEAST 2 positions NOT only 2 positions. 
    printf("Print an int = %2d\n", 1000000);
/*
Print an int = 100
Print an int =    100
*/ 

    char fmt_str[] = "%3d"; // sizeof(fmt_str) == 2?
    printf("sizeof(fmt_str) = %lu\n", sizeof(fmt_str)); // NO! sizeof(fmt_str) == 4!!!!!!!!!! The % and d are separate chars. only the print function knows it is a place holder for a single argument. 
    //int sprintf(char *string, char *format, arg1, arg2, ...);
    printf("sizeof(MY_STR_FMT_STRING) = %lu \n", sizeof(MY_STR_FMT_STRING)); //expect 23
    
    static char fstr[sizeof(MY_STR_FMT_STRING)];
    printf("sizeof(fstr) = %lu \n", sizeof(fstr)); //expect 23

    int http_status = 204; 
    sprintf(fstr, MY_STR_FMT_STRING, http_status);
    printf("%s\n", fstr);
}

void machine_dependent_sign_mod(void) {
    int n = 114;

    // K&R 2.5 Arithmetic operators
    /*
        The direction of truncation for / and the sign of the result for % are 
        machine-dependent for negative operands, as is the action taken on 
        overflow or underflow.
    */

    printf("%d mod 10 = %d , %d mod -10 = %d\n", n, n%10, n, n%-10);
}

void sizeof_no_parens(void) {
    int n;
    printf("size of no paren = %lu", sizeof n); // it works! dont forget to match the format str to the type!! you asshole
}

void escape_chars_and_constants(void) {
    char tmp[] = "\n \t \\ \' // ";
    char c = '\'';
    char a = '\"';
    char c2 = '"'; // this is allowed
    char s[] = " 'hello' \"";
    printf("%s\n",s);
}

void comment_in_expression(void){
    int i = 0;

    i = i + /* is this legal ? */1; // yes, it is legal.
    //i = 3; /* what about this? *                   / nope, this one isn't legal.
    i = 4; // hello \
    bro
    i=5; // ohh shit, bro. above is legal.
    printf("yo\n");
}

#define MAX_SERIAL_PRINT_SIZE 0x6U


void num_chunks_calc(char *str) {
    unsigned int numchunks;
    unsigned int len;
    static char buffer[MAX_SERIAL_PRINT_SIZE+1];

    len = strlen(str);
    printf("len = %u, max=%u, len/max=%u, len%%max=%u\n", len, MAX_SERIAL_PRINT_SIZE, len/MAX_SERIAL_PRINT_SIZE, len%MAX_SERIAL_PRINT_SIZE);

    if(len > MAX_SERIAL_PRINT_SIZE) {
        numchunks = len/MAX_SERIAL_PRINT_SIZE + ((len%MAX_SERIAL_PRINT_SIZE == 0)? 0U:1U);
    } else {
        printf("%s", buffer);
        return;
    }

    printf("numchunks = %u\n", numchunks);

    while(numchunks--){
        strncpy(buffer, str, MAX_SERIAL_PRINT_SIZE);
        printf("%s", buffer);
        str += MAX_SERIAL_PRINT_SIZE;
    }

}

void test_num_chunks_calc(void) {
    num_chunks_calc("hello world");
    num_chunks_calc("If I have done the public any service it is due to my patient thought.");
}


void test_wide_str_pointer_arithmetic(void) {
  wchar_t str[] = L"/rest/v1/systems/1/bios/settings";
  wchar_t *start;
  wchar_t *end;

  start = &str[9];
  end = &str[16];
  printf("str=%S\nstart=%S\nend=%S\ndiff=%lu\nlen=%lu\n", str, start, end, (void*)end-(void*)start,sizeof(wchar_t)); // end - start gives the proper length of the URI segment. 

}

// Recursively creates a directory structure based on the given URI.
// e.g. if Uri = "/rest/v1/providers" this function will create 3 nested directories
// equivalent to the following system calls,
// mkdir rest
// mkdir rest/v1
// mkdir rest/v1/providers
// pre-conditions: Uri always begins with a '/' character. The max node length is <= 20. Uri does NOT end in a / character
char *
MkDirFromUri(
  char *Uri,
  char *LastNode
  ) 
{
  char        CmdStr[256];
  char        DirName[256];
  char        *Start;
  char        *End;
  int         Status;

  if(Uri ==  NULL) {
    printf("Uri = NULL.\n");
    return NULL;
  }

  if(strlen(Uri) == 0) { // Nothing to do. 
    printf("len = 0.\n");
    return NULL;
  }

  if(Uri[0] != '/') { // Enforce that all Uri's passed to this function start with a /
    printf("Uri[0] != /\n");
    return NULL;
  }

  //
  // Find the start and end of the node that URI begins with.
  //
  Start = Uri+1; // Start point to the char. immediately after the first /.
  End   = Uri+1;

  while (*End != '\0' && *End != '/') { // Advance End pointer to the next /. If we have reached the last node than we advanced to the end of the Uri string.
    End++;
  }

  DirName[0] = '\0';
  if(LastNode != NULL) { // Append the last node extracted from the Uri.
    strcat(DirName, LastNode);
    strcat(DirName, "/");
  }

  strncat(DirName, Start, End - Start); // cat. the next node.
  //
  // Create the directory for this node.
  //
  sprintf(CmdStr, "%s %s", "mkdir ", DirName); ////** in bash you can do the entire thing in one command with e.g. "mkdir -p rest/v1/providers" and delete all with "rm -R rest" ///// // account for max node len - do a sanity check and handle gracefully. 
  printf("running command: %s\n", CmdStr);
  system(CmdStr); 
  
  //if(Status) {
   // printf("Command failed. Status = %d.\n", Status);
   // return NULL;
  //}
  //zeromem CmdStr
  
  //sprintf(CmdStr, "%s %s", "cd ", DirName);
  //printf("running command: %s\n", CmdStr);
  //Status = system(CmdStr); // cd into the directory we just created

  //if(Status) {
    //printf("Command failed. Status = %d.\n", Status);
    //return NULL;
  //}

  if(*End == '\0') { // this was the last node.
    printf("Done.\n");
    // cd back to root here?
    return NULL;
  }

  return MkDirFromUri(End, DirName); // recursively create the directory for the next node in URI.

  //next - skim for typos or bugs, especially at boundary conditions. 
}