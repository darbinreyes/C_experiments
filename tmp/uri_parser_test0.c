#include <stdio.h>
#include <Uri.h>

// compilation:  cc uri_parser_test0.c -I /opt/local/include/uriparser/ -L/opt/local/lib/ -luriparser

void test0(void) {
  UriParserStateA state;
  UriUriA uri;

  state.uri = &uri;
  if (uriParseUriA(&state, "file:///home/user/song.mp3") != URI_SUCCESS) {
    /* Failure */
    uriFreeUriMembersA(&uri);
    // ...
    printf("Failure, uriparser.\n");
  }
  // ...
  printf("KK, uriparser. scheme = %*s.\n", (int)(uri.scheme.afterLast - uri.scheme.first), uri.scheme.first);
  printf("KK, uriparser. len = %d. pathTail.text = %*s.\n", (int)(uri.pathTail->text.afterLast - uri.pathTail->text.first),(int)(uri.pathTail->text.afterLast - uri.pathTail->text.first), uri.pathTail->text.first);
  uriFreeUriMembersA(&uri);
}

int main(void) {
  printf("Hello, uriparser.\n");
  test0();
  return 0;
}