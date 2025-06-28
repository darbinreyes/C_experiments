#include <stdio.h>
#include <signal.h>
//volatile sig_atomic_t flag = 0; // volatile ensures compiler doesn't optimize reads/writes
int flag;
void handler(int signum);
// void handler(int signum) {
//     flag = 1; // Modified asynchronously
//     printf("handled\n");
// }
int main() {
    signal(SIGINT, handler);
    while (!flag) { // Compiler won't cache flag's value due to volatile
        // Work
        printf("working\n");
    }
    return 0;
}