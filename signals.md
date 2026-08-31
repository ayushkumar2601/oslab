# 7. Signals — C Programs

## 1. Catch SIGCHLD from Child Process

### Code

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig) {
    printf("SIGCHLD received: Child terminated\n");
}

int main() {
    signal(SIGCHLD, handler);

    if (fork() == 0) {
        printf("Child running...\n");
        sleep(2);
        return 0;
    }

    wait(NULL);
    printf("Parent finished\n");
    return 0;
}
```

### How to Run

```bash
gcc q1.c -o q1
./q1
```

---

## 2. Handle SIGINT Signal

### Code

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("SIGINT received by user/process\n");
}

int main() {
    signal(SIGINT, handler);

    printf("Press Ctrl+C...\n");

    while (1)
        sleep(1);

    return 0;
}
```

### How to Run

```bash
gcc q2.c -o q2
./q2
```

Press **Ctrl+C** to generate `SIGINT`.

---

## 3. Ignore SIGINT and Restore Default Status

### Code

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    signal(SIGINT, SIG_IGN);

    printf("SIGINT ignored. Ctrl+C will not kill me.\n");
    sleep(5);

    signal(SIGINT, SIG_DFL);
    printf("Default SIGINT restored. Press Ctrl+C now.\n");

    while (1)
        sleep(1);

    return 0;
}
```

### How to Run

```bash
gcc q3.c -o q3
./q3
```

Press **Ctrl+C** during the first 5 seconds — nothing happens.

After 5 seconds, press **Ctrl+C** again — the process terminates.

---

## 4. Wake Processes A and B Using Signals

### Code

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void awake(int sig) {
    printf("I am awake\n");
    _exit(0);
}

int main() {
    pid_t a, b;

    if ((a = fork()) == 0) {
        signal(SIGUSR1, awake);
        printf("Process A: PID = %d\n", getpid());
        while (1) pause();
    }

    if ((b = fork()) == 0) {
        signal(SIGUSR2, awake);
        printf("Process B: PID = %d\n", getpid());
        while (1) pause();
    }

    wait(NULL);
    wait(NULL);

    return 0;
}
```

### How to Run

```bash
gcc q4.c -o q4
./q4
```

You will see something like:

```text
Process A: PID = 1234
Process B: PID = 1235
```

Open another terminal and send signals:

```bash
kill -USR1 1234
kill -USR2 1235
```

Both processes will print:

```text
I am awake
```

and terminate.

---

## 5. Wait for Child for Given Delay

### Code

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int status, delay = atoi(argv[1]);
    pid_t p = fork();

    if (p == 0) {
        printf("Child working...\n");
        sleep(3);
        return 10;
    }

    sleep(delay);

    if (waitpid(p, &status, WNOHANG) == 0) {
        printf("Child did not finish. Killing it...\n");
        kill(p, SIGKILL);
        wait(NULL);
    } else {
        printf("Child PID: %d, Status: %d\n",
               p, WEXITSTATUS(status));
    }

    return 0;
}
```

### How to Run

Compile:

```bash
gcc q5.c -o q5
```

Run with a delay:

```bash
./q5 5
```

Since the child takes 3 seconds and the delay is 5 seconds, the child finishes normally:

```text
Child working...
Child PID: 1234, Status: 10
```

Try a smaller delay:

```bash
./q5 2
```

The parent kills the child because it does not finish within 2 seconds:

```text
Child working...
Child did not finish. Killing it...
```

---

# Quick Compilation

If all files are in the same folder:

```bash
gcc q1.c -o q1
gcc q2.c -o q2
gcc q3.c -o q3
gcc q4.c -o q4
gcc q5.c -o q5
```

Then run:

```bash
./q1
./q2
./q3
./q4
./q5 5
```
