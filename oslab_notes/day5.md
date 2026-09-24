# Day 5: Threads-1

**1. Write a program to create a thread that displays a WELCOME message.**
```c
#include <stdio.h>
#include <pthread.h>
void* msg(void* arg) {
    printf("WELCOME\n");
    return NULL;
}
int main() {
    pthread_t t;
    pthread_create(&t, NULL, msg, NULL);
    pthread_join(t, NULL);
    return 0;
}
```

**2. Write a program that creates multiple threads and terminate those. The program should create 5 threads with the pthread_create() routine. Each thread prints a “Hello World!” message and then terminates with a call to pthread_exit().**
```c
#include <stdio.h>
#include <pthread.h>
void* msg(void* arg) {
    printf("Hello World!\n");
    pthread_exit(NULL);
}
int main() {
    pthread_t t[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&t[i], NULL, msg, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}
```

**3. Write a program which implements thread with arguments and thread joining.**
```c
#include <stdio.h>
#include <pthread.h>
void* msg(void* arg) {
    int val = *(int*)arg;
    printf("Argument: %d\n", val);
    return NULL;
}
int main() {
    pthread_t t;
    int arg = 10;
    pthread_create(&t, NULL, msg, &arg);
    pthread_join(t, NULL);
    return 0;
}
```
