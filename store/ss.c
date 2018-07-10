#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0
 
void* helloWorld(void *args) {
    printf("Hello from thread!\n");
    return SUCCESS;
}
 
int main() {
    pthread_t thread;
    int status;
    int status_addr;
 
    status = pthread_create(&thread, NULL, helloWorld, NULL);
    printf("Hello from main!\n");
 
    status = pthread_join(thread, (void**)&status_addr);
 
    printf("joined with address %d\n", status_addr);
    return 0;
}
