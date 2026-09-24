# Day 4: Process-2

**1. Write a program that creates three child processes. The first child process executes the command “who”, the second child process executes the command “ls” passing it the parameter “–al” using execlp(..) C function and the third child process executes the command “date” with path ”/bin/date” in execl() C function. The parent process waits for all the child processes to finish and prints the termination status of the child.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t p1 = fork();
    if (p1 == 0) execlp("who", "who", NULL);
    pid_t p2 = fork();
    if (p2 == 0) execlp("ls", "ls", "-al", NULL);
    pid_t p3 = fork();
    if (p3 == 0) execl("/bin/date", "date", NULL);
    int status;
    waitpid(p1, &status, 0);
    printf("Child 1 terminated with status: %d\n", WEXITSTATUS(status));
    waitpid(p2, &status, 0);
    printf("Child 2 terminated with status: %d\n", WEXITSTATUS(status));
    waitpid(p3, &status, 0);
    printf("Child 3 terminated with status: %d\n", WEXITSTATUS(status));
    return 0;
}
```

**2. Write a program to create a process which will run as a background process for fifty seconds and at the time of execution it will print the system information.**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        system("uname -a");
        sleep(50);
        exit(0);
    }
    return 0;
}
```

**3. Write a program that creates two child processes. Each of the child process prints numbers from 1 to 10. Each time a child prints a number it also prints its own PID and parent PID. The parent waits for both of its child to finish execution and prints “Good Bye” before exiting.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
void print_nums() {
    for (int i = 1; i <= 10; i++) {
        printf("%d, PID: %d, PPID: %d\n", i, getpid(), getppid());
    }
    exit(0);
}
int main() {
    pid_t p1 = fork();
    if (p1 == 0) print_nums();
    pid_t p2 = fork();
    if (p2 == 0) print_nums();
    wait(NULL);
    wait(NULL);
    printf("Good Bye\n");
    return 0;
}
```
