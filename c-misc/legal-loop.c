// foo bar


void foo () {
    while(;;); // illegal
}

int main(void) {
    for (;;);  // legal - infinite loop
    while();   // illegal
    while(;;); // illegal
    // why? an empty condition in a for loop is syntactically defined as true (non-zero)
}