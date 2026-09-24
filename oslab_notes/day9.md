# Day 9: Semaphores

**1. Solve the producer consumer problem for a single piece of data using binary semaphore.**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t empty, full;
int data;
void* producer(void* arg) {
    sem_wait(&empty);
    data = 1;
    sem_post(&full);
    return NULL;
}
void* consumer(void* arg) {
    sem_wait(&full);
    printf("%d\n", data);
    sem_post(&empty);
    return NULL;
}
int main() {
    pthread_t p, c;
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}
```

**2. Solve the above problem for two consumer processes.**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t empty, full;
int data;
void* producer(void* arg) {
    sem_wait(&empty);
    data = 1;
    sem_post(&full);
    sem_post(&full);
    return NULL;
}
void* consumer(void* arg) {
    sem_wait(&full);
    printf("%d\n", data);
    return NULL;
}
int main() {
    pthread_t p, c1, c2;
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c1, NULL, consumer, NULL);
    pthread_create(&c2, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
    return 0;
}
```

**3. Solve the producer problem by a bounded length array.**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5
sem_t empty, full, mutex;
int buf[N], in = 0, out = 0;
void* producer(void* arg) {
    sem_wait(&empty);
    sem_wait(&mutex);
    buf[in] = 1;
    in = (in + 1) % N;
    sem_post(&mutex);
    sem_post(&full);
    return NULL;
}
void* consumer(void* arg) {
    sem_wait(&full);
    sem_wait(&mutex);
    int item = buf[out];
    out = (out + 1) % N;
    printf("%d\n", item);
    sem_post(&mutex);
    sem_post(&empty);
    return NULL;
}
int main() {
    pthread_t p, c;
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    return 0;
}
```

**4. Write a program that uses several Pthread condition variable routines. The main routine creates three threads. Two of the threads perform work and update a "count" variable. The third thread waits until the count variable reaches a specified value (say 500).**
```c
#include <stdio.h>
#include <pthread.h>
pthread_mutex_t m;
pthread_cond_t c;
int count = 0;
void* worker(void* arg) {
    for (int i = 0; i < 300; i++) {
        pthread_mutex_lock(&m);
        count++;
        if (count == 500) pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}
void* waiter(void* arg) {
    pthread_mutex_lock(&m);
    while (count < 500) pthread_cond_wait(&c, &m);
    printf("Count reached 500\n");
    pthread_mutex_unlock(&m);
    return NULL;
}
int main() {
    pthread_t t1, t2, t3;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);
    pthread_create(&t3, NULL, waiter, NULL);
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    pthread_join(t1, NULL); pthread_join(t2, NULL); pthread_join(t3, NULL);
    return 0;
}
```

**5. Implement Dining Philosophers problem.**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t f[5];
void* phil(void* arg) {
    int i = *(int*)arg;
    sem_wait(&f[i]);
    sem_wait(&f[(i+1)%5]);
    printf("%d eating\n", i);
    sem_post(&f[(i+1)%5]);
    sem_post(&f[i]);
    return NULL;
}
int main() {
    pthread_t t[5];
    int id[5];
    for (int i=0; i<5; i++) sem_init(&f[i], 0, 1);
    for (int i=0; i<5; i++) { id[i]=i; pthread_create(&t[i], NULL, phil, &id[i]); }
    for (int i=0; i<5; i++) pthread_join(t[i], NULL);
    return 0;
}
```
