#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//volatile int stop = 0; // volatile ensures visibility of changes across threads
int stop = 0;
void* thread_func(void* arg) {
    while (!stop) { // Compiler won't cache stop
        // Work
        printf("working\n");
    }
    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, thread_func, NULL);
    sleep(1);
    stop = 1; // Signal thread to stop
    pthread_join(t, NULL);
    return 0;
}