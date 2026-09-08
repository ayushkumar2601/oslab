````md
# 7 Signals Programs in C

All programs use Linux/POSIX system calls.

Compile using:

```bash
gcc filename.c -o filename
````

---

## 1. Catch SIGCHLD When Child Terminates

### Code: `sigchld.c`

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig) {
    printf("SIGCHLD received: Child terminated\n");
    wait(NULL);
}

int main() {
    if (fork() == 0) {
        printf("Child running...\n");
        sleep(2);
        return 0;
    }

    signal(SIGCHLD, handler);
    wait(NULL);

    return 0;
}
```

### Run

```bash
gcc sigchld.c -o sigchld
./sigchld
```

---

## 2. Print SIGINT Message and User

### Code: `sigint.c`

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pwd.h>

void handler(int sig) {
    printf("\nSIGINT received!\n");
    printf("User: %s\n", getpwuid(getuid())->pw_name);
}

int main() {
    signal(SIGINT, handler);
    printf("Press Ctrl+C\n");

    while (1)
        pause();

    return 0;
}
```

### Run

```bash
gcc sigint.c -o sigint
./sigint
```

Press **Ctrl+C** to test.

---

## 3. Ignore Ctrl+C and Restore Default SIGINT

### Code: `ignore_sigint.c`

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("Ctrl+C ignored for 5 seconds...\n");

    signal(SIGINT, SIG_IGN);
    sleep(5);

    printf("SIGINT restored. Press Ctrl+C.\n");
    signal(SIGINT, SIG_DFL);

    while (1)
        pause();

    return 0;
}
```

### Run

```bash
gcc ignore_sigint.c -o ignore_sigint
./ignore_sigint
```

Press **Ctrl+C** during the first 5 seconds. It will be ignored.

After 5 seconds, pressing **Ctrl+C** terminates the process.

---

## 4. Processes A and B Wake Using SIGUSR1 and SIGUSR2

### Code: `usr_signals.c`

```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void a(int s) {
    printf("Process A: I am awake\n");
    _exit(0);
}

void b(int s) {
    printf("Process B: I am awake\n");
    _exit(0);
}

int main() {
    int A = fork();

    if (A == 0) {
        signal(SIGUSR1, a);
        while (1)
            pause();
    }

    int B = fork();

    if (B == 0) {
        signal(SIGUSR2, b);
        while (1)
            pause();
    }

    sleep(1);
    kill(A, SIGUSR1);
    kill(B, SIGUSR2);

    return 0;
}
```

### Run

```bash
gcc usr_signals.c -o usr_signals
./usr_signals
```

### Output

```text
Process A: I am awake
Process B: I am awake
```

---

## 5. Wait for Child for Given Delay, Then Kill if Necessary

### Code: `delay.c`

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <delay>\n", argv[0]);
        return 1;
    }

    int delay = atoi(argv[1]);
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child running...\n");
        sleep(3);
        return 42;
    }

    sleep(delay);

    if (waitpid(pid, NULL, WNOHANG) == 0) {
        printf("Child did not finish. Killing PID %d\n", pid);
        kill(pid, SIGKILL);
        wait(NULL);
    } else {
        int status;
        waitpid(pid, &status, 0);
        printf("Child PID: %d, Status: %d\n",
               pid, WEXITSTATUS(status));
    }

    return 0;
}
```

### Run

Compile:

```bash
gcc delay.c -o delay
```

Run with a delay of 5 seconds:

```bash
./delay 5
```

The child takes 3 seconds, so it finishes within the delay.

Example output:

```text
Child running...
Child PID: 12345, Status: 42
```

Run with a delay of 1 second:

```bash
./delay 1
```

The parent kills the child because it does not finish within 1 second.

Example output:

```text
Child running...
Child did not finish. Killing PID 12345
```

---

# Quick Compile & Run

```bash
gcc sigchld.c -o sigchld
./sigchld

gcc sigint.c -o sigint
./sigint

gcc ignore_sigint.c -o ignore_sigint
./ignore_sigint

gcc usr_signals.c -o usr_signals
./usr_signals

gcc delay.c -o delay
./delay 5
```

> **Note:** These programs are intended for Linux/Unix systems and use POSIX functions such as `fork()`, `signal()`, `kill()`, `wait()`, `waitpid()`, and `pause()`.

```
```
