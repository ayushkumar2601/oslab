# Day 8: Inter-process Communication – Pipes

**1. Write a code in C to implement how a process communicates with another process using the pipe function.**
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    int p[2];
    char buf[20];
    pipe(p);
    if (fork() == 0) {
        write(p[1], "hello", 5);
    } else {
        read(p[0], buf, 5);
        printf("%s\n", buf);
    }
    return 0;
}
```

**2. Write a code in C to implement how a process communicates with another process using the popen function.**
```c
#include <stdio.h>
int main() {
    FILE *f = popen("ls", "r");
    char buf[100];
    while (fgets(buf, 100, f) != NULL) {
        printf("%s", buf);
    }
    pclose(f);
    return 0;
}
```

**3. Write a program that creates a one-way pipe between a parent and child process. The parent process gets a string from standard input and sends the string to the child. The child prints the reverse of the string. Both parent and child terminates when the string “quit” is input.**
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main() {
    int p[2];
    pipe(p);
    if (fork() == 0) {
        char buf[100];
        while (1) {
            read(p[0], buf, 100);
            if (strcmp(buf, "quit\n") == 0) break;
            int len = strlen(buf) - 1;
            for (int i = len - 1; i >= 0; i--) printf("%c", buf[i]);
            printf("\n");
        }
    } else {
        char str[100];
        while (1) {
            fgets(str, 100, stdin);
            write(p[1], str, 100);
            if (strcmp(str, "quit\n") == 0) break;
        }
    }
    return 0;
}
```

**4. Write a program that creates a two-way pipe between a parent and child process. The parent process gets an integer from standard input and sends the integer to the child and the child computes the sum of all integers up to the input value received from parent and sends the result back to the parent process, which then prints it. Both the parent and child terminates when the number 0 is input.**
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    int p1[2], p2[2];
    pipe(p1); pipe(p2);
    if (fork() == 0) {
        int n, sum;
        while (1) {
            read(p1[0], &n, sizeof(n));
            if (n == 0) break;
            sum = 0;
            for (int i = 1; i <= n; i++) sum += i;
            write(p2[1], &sum, sizeof(sum));
        }
    } else {
        int n, sum;
        while (1) {
            scanf("%d", &n);
            write(p1[1], &n, sizeof(n));
            if (n == 0) break;
            read(p2[0], &sum, sizeof(sum));
            printf("%d\n", sum);
        }
    }
    return 0;
}
```

**5. Write a program that creates one-way pipe between a parent and three child processes. The parent process gets an integer number range from standard input and divides the entire range to three child processes. Each of the child after receiving the sub-range, searches for prime numbers in that range and prints them.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
void child(int fd) {
    int r[2];
    read(fd, r, sizeof(r));
    for (int i = r[0]; i <= r[1]; i++) {
        int f = 0;
        for (int j = 2; j <= i/2; j++) {
            if (i % j == 0) { f = 1; break; }
        }
        if (f == 0 && i > 1) printf("Prime: %d\n", i);
    }
}
int main() {
    int p1[2], p2[2], p3[2];
    pipe(p1); pipe(p2); pipe(p3);
    if (fork() == 0) { child(p1[0]); return 0; }
    if (fork() == 0) { child(p2[0]); return 0; }
    if (fork() == 0) { child(p3[0]); return 0; }
    int start, end;
    scanf("%d %d", &start, &end);
    int step = (end - start + 1) / 3;
    int r1[2] = {start, start + step - 1};
    int r2[2] = {start + step, start + 2 * step - 1};
    int r3[2] = {start + 2 * step, end};
    write(p1[1], r1, sizeof(r1));
    write(p2[1], r2, sizeof(r2));
    write(p3[1], r3, sizeof(r3));
    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}
```
