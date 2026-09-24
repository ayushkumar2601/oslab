# Day 6: Threads-2

**1. Write a multi-threaded program where the main thread gets an integer number range from the user and then creates two child threads; one thread finds odd numbers in the range and print them, and the second thread finds even numbers in the range and prints them. The child thread must terminate by returning a value. The parent thread must wait for the child threads to finish and it must also print the return values of the child threads.**
```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct Range { int start, end; };
void* odd(void* arg) {
    struct Range* r = (struct Range*)arg;
    for (int i = r->start; i <= r->end; i++) {
        if (i % 2 != 0) printf("Odd: %d\n", i);
    }
    return (void*)1;
}
void* even(void* arg) {
    struct Range* r = (struct Range*)arg;
    for (int i = r->start; i <= r->end; i++) {
        if (i % 2 == 0) printf("Even: %d\n", i);
    }
    return (void*)2;
}
int main() {
    pthread_t t1, t2;
    struct Range r;
    scanf("%d %d", &r.start, &r.end);
    pthread_create(&t1, NULL, odd, &r);
    pthread_create(&t2, NULL, even, &r);
    void *ret1, *ret2;
    pthread_join(t1, &ret1);
    pthread_join(t2, &ret2);
    printf("Ret1: %ld, Ret2: %ld\n", (long)ret1, (long)ret2);
    return 0;
}
```

**2. Write a multi-threaded program where the main thread gets an integer number range from the user and then creates two child threads; one thread calculates the sum of all numbers in the range and prints it, and the second thread finds prime numbers in the range and prints them. The child thread must terminate by returning a value. The parent thread must wait for the child threads to finish, and it must also print the return values of the child threads.**
```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct Range { int start, end; };
void* sum(void* arg) {
    struct Range* r = (struct Range*)arg;
    long s = 0;
    for (int i = r->start; i <= r->end; i++) s += i;
    printf("Sum: %ld\n", s);
    return (void*)1;
}
void* prime(void* arg) {
    struct Range* r = (struct Range*)arg;
    for (int i = r->start; i <= r->end; i++) {
        int f = 0;
        for (int j = 2; j <= i/2; j++) {
            if (i % j == 0) { f = 1; break; }
        }
        if (f == 0 && i > 1) printf("Prime: %d\n", i);
    }
    return (void*)2;
}
int main() {
    pthread_t t1, t2;
    struct Range r;
    scanf("%d %d", &r.start, &r.end);
    pthread_create(&t1, NULL, sum, &r);
    pthread_create(&t2, NULL, prime, &r);
    void *ret1, *ret2;
    pthread_join(t1, &ret1);
    pthread_join(t2, &ret2);
    printf("Ret1: %ld, Ret2: %ld\n", (long)ret1, (long)ret2);
    return 0;
}
```
