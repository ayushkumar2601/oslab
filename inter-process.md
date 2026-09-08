````md
# 8. Inter-Process Communication – Pipes

All programs are written in C and use Linux/POSIX system calls.

Compile using:

```bash
gcc filename.c -o filename
````

---

## 1. Process Communication Using `pipe()`

### Question

Write a code in C to implement how a process communicates with another process using the `pipe()` function.

### Code: `pipe.c`

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p[2];
    char msg[] = "Hello from parent";
    char buf[50];

    pipe(p);

    if (fork() == 0) {
        close(p[1]);
        read(p[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
    } else {
        close(p[0]);
        write(p[1], msg, strlen(msg) + 1);
    }

    return 0;
}
```

### Run

```bash
gcc pipe.c -o pipe
./pipe
```

### Output

```text
Child received: Hello from parent
```

---

## 2. Process Communication Using `popen()`

### Question

Write a code in C to implement how a process communicates with another process using the `popen()` function.

### Code: `popen.c`

```c
#include <stdio.h>

int main() {
    char buf[100];
    FILE *p = popen("echo Hello from child", "r");

    fgets(buf, sizeof(buf), p);
    printf("Parent received: %s", buf);

    pclose(p);
    return 0;
}
```

### Run

```bash
gcc popen.c -o popen
./popen
```

### Output

```text
Parent received: Hello from child
```

---

## 3. One-Way Pipe – Reverse String

### Question

Write a program that creates a one-way pipe between a parent and child process. The parent gets a string from standard input and sends it to the child. The child prints the reverse of the string. Both parent and child terminate when the string `quit` is input.

### Code: `reverse_pipe.c`

```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p[2];
    char s[100];
    pipe(p);

    if (fork() == 0) {
        close(p[1]);

        while (read(p[0], s, sizeof(s))) {
            if (!strcmp(s, "quit\n"))
                break;

            int n = strlen(s);
            for (int i = n - 1; i >= 0; i--)
                putchar(s[i]);
        }
    } else {
        close(p[0]);

        while (fgets(s, sizeof(s), stdin)) {
            write(p[1], s, strlen(s) + 1);

            if (!strcmp(s, "quit\n"))
                break;
        }
    }

    return 0;
}
```

### Run

```bash
gcc reverse_pipe.c -o reverse_pipe
./reverse_pipe
```

### Example

```text
hello
olleh
world
dlrow
quit
```

---

## 4. Two-Way Pipe – Sum of Integers

### Question

Write a program that creates a two-way pipe between a parent and child process. The parent gets an integer and sends it to the child. The child computes the sum of all integers up to the input value and sends the result back to the parent. Both terminate when `0` is input.

### Code: `sum_pipe.c`

```c
#include <stdio.h>
#include <unistd.h>

int main() {
    int p[2], q[2], n, sum;
    pipe(p);
    pipe(q);

    if (fork() == 0) {
        close(p[1]);
        close(q[0]);

        while (read(p[0], &n, sizeof(n))) {
            if (n == 0)
                break;

            sum = n * (n + 1) / 2;
            write(q[1], &sum, sizeof(sum));
        }
    } else {
        close(p[0]);
        close(q[1]);

        while (1) {
            scanf("%d", &n);
            write(p[1], &n, sizeof(n));

            if (n == 0)
                break;

            read(q[0], &sum, sizeof(sum));
            printf("Sum = %d\n", sum);
        }
    }

    return 0;
}
```

### Run

```bash
gcc sum_pipe.c -o sum_pipe
./sum_pipe
```

### Example

```text
5
Sum = 15
10
Sum = 55
7
Sum = 28
0
```

---

## 5. One-Way Pipe – Three Child Processes Finding Primes

### Question

Write a program that creates a one-way pipe between a parent and three child processes. The parent gets an integer range and divides the range among three children. Each child receives its sub-range, searches for prime numbers, and prints them.

### Code: `prime_pipe.c`

```c
#include <stdio.h>
#include <unistd.h>

int prime(int n) {
    if (n < 2) return 0;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;

    return 1;
}

int main() {
    int p[2], a, b, n, x, y;
    pipe(p);

    printf("Enter range: ");
    scanf("%d%d", &a, &b);

    n = (b - a + 1) / 3;

    for (int k = 0; k < 3; k++) {
        if (fork() == 0) {
            close(p[1]);

            read(p[0], &x, sizeof(x));
            read(p[0], &y, sizeof(y));

            printf("Child %d: ", k + 1);
            for (int i = x; i <= y; i++)
                if (prime(i))
                    printf("%d ", i);
            printf("\n");

            return 0;
        }
    }

    close(p[0]);

    for (int k = 0; k < 3; k++) {
        x = a + k * n;
        y = (k == 2) ? b : x + n - 1;

        write(p[1], &x, sizeof(x));
        write(p[1], &y, sizeof(y));
    }

    return 0;
}
```

### Run

```bash
gcc prime_pipe.c -o prime_pipe
./prime_pipe
```

### Example

```text
Enter range: 1 30
Child 1: 2 3 5 7
Child 2: 11 13 17
Child 3: 19 23 29
```

> **Note:** The order in which the three child processes print may vary because they execute concurrently.

---

# Quick Compile & Run

```bash
gcc pipe.c -o pipe
./pipe

gcc popen.c -o popen
./popen

gcc reverse_pipe.c -o reverse_pipe
./reverse_pipe

gcc sum_pipe.c -o sum_pipe
./sum_pipe

gcc prime_pipe.c -o prime_pipe
./prime_pipe
```

## Requirements

These programs are designed for Linux/Unix systems and use POSIX functions such as:

* `pipe()`
* `fork()`
* `read()`
* `write()`
* `popen()`
* `pclose()`

```
```
