# Day 3: Process-1

**1. Creation of a process.**
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    fork();
    printf("Process created\n");
    return 0;
}
```

**2. Write a program to get the PID of parent and child process.**
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else if (pid > 0) {
        printf("Parent PID: %d, Child PID: %d\n", getpid(), pid);
    }
    return 0;
}
```

**3. Implement an orphan process using fork.**
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent terminates\n");
    } else if (pid == 0) {
        sleep(2);
        printf("Orphan child PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    return 0;
}
```

**4. Implement a zombie process using fork.**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    pid_t pid = fork();
    if (pid > 0) {
        sleep(5);
    } else if (pid == 0) {
        exit(0);
    }
    return 0;
}
```

**5. Write a program with a local variable and a global variable. Initialize both of them. The program should fork a child process and the child should increment both the variables by 1. After this operation, both the parent and the child should print the values of the variable.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int g = 10;
int main() {
    int l = 20;
    pid_t pid = fork();
    if (pid == 0) {
        g++;
        l++;
        printf("Child - g: %d, l: %d\n", g, l);
    } else if (pid > 0) {
        wait(NULL);
        printf("Parent - g: %d, l: %d\n", g, l);
    }
    return 0;
}
```

**6. Implement the assignment no. 5 using vfork for spawning the child.**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int g = 10;
int main() {
    int l = 20;
    pid_t pid = vfork();
    if (pid == 0) {
        g++;
        l++;
        printf("Child - g: %d, l: %d\n", g, l);
        exit(0);
    } else if (pid > 0) {
        wait(NULL);
        printf("Parent - g: %d, l: %d\n", g, l);
    }
    return 0;
}
```
