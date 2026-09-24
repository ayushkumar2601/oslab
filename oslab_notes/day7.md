# Day 7: Signals

**1. Write a program to create a child process. The parent catches a SIGCHLD signal from the child process when the child terminates.**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
void handler(int sig) {
    printf("Caught SIGCHLD\n");
}
int main() {
    signal(SIGCHLD, handler);
    pid_t pid = fork();
    if (pid == 0) {
        exit(0);
    } else {
        wait(NULL);
    }
    return 0;
}
```

**2. Write a program to print the default message of SIGINT signal and also prints the user.**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void handler(int sig) {
    printf("Caught SIGINT. User: %s\n", getenv("USER"));
    exit(0);
}
int main() {
    signal(SIGINT, handler);
    while(1) pause();
    return 0;
}
```

**3. Write a program for a process which cannot be killed by pressing Ctrl + c and again restore the default status of it.**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
int main() {
    printf("Ignoring SIGINT\n");
    signal(SIGINT, SIG_IGN);
    sleep(5);
    printf("Restoring SIGINT\n");
    signal(SIGINT, SIG_DFL);
    sleep(5);
    return 0;
}
```

**4. Process A and Process B normally sleep, except when process A receives signal SIGUSR1 and process B receives signal SIGUSR2, when both the processes prints the message “I am awake” and terminate. Write a program to incorporate this.**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void handler(int sig) {
    printf("I am awake\n");
    exit(0);
}
int main() {
    pid_t pb = fork();
    if (pb == 0) {
        signal(SIGUSR2, handler);
        while(1) pause();
    }
    pid_t pa = fork();
    if (pa == 0) {
        signal(SIGUSR1, handler);
        while(1) pause();
    }
    sleep(1);
    kill(pa, SIGUSR1);
    kill(pb, SIGUSR2);
    return 0;
}
```

**5. Write a program which takes a value of delay as command line argument and creates a child process. The parent process waits for the child process to finish its job up to the supplied delay value. If the child terminates within the delay the parent prints the termination status and PID of the child process. On not receiving from the child it kills the child process forcefully.**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
int main(int argc, char *argv[]) {
    int delay = atoi(argv[1]);
    pid_t pid = fork();
    if (pid == 0) {
        sleep(2);
        exit(0);
    }
    int status, waited = 0;
    while (waited < delay) {
        pid_t res = waitpid(pid, &status, WNOHANG);
        if (res == pid) {
            printf("Child %d terminated, status: %d\n", pid, WEXITSTATUS(status));
            return 0;
        }
        sleep(1);
        waited++;
    }
    kill(pid, SIGKILL);
    printf("Killed forcefully\n");
    return 0;
}
```
