# Common Steps

Create file:

```bash
nano q1.c
```

Paste code, then:

**Save:** `Ctrl + O`, Enter
**Exit:** `Ctrl + X`

Compile:

```bash
gcc q1.c -o q1
```

Run:

```bash
./q1
```

---

# 1. Creation of a Process

### File: q1.c

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    fork();

    printf("Process Created\n");

    return 0;
}
```

### Compile

```bash
gcc q1.c -o q1
```

### Run

```bash
./q1
```

### Output

```text
Process Created
Process Created
```

Because both parent and child execute the `printf()`.

---

# 2. PID of Parent and Child

### File: q2.c

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);
    }

    return 0;
}
```

### Compile

```bash
gcc q2.c -o q2
```

### Run

```bash
./q2
```

---

# 3. Orphan Process using fork()

Parent terminates before child.

### File: q3.c

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        sleep(5);

        printf("Child Process\n");
        printf("Child PID = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());
    }
    else
    {
        printf("Parent Exiting...\n");
    }

    return 0;
}
```

### Compile

```bash
gcc q3.c -o q3
```

### Run

```bash
./q3
```

### Explanation

* Parent exits immediately.
* Child waits 5 seconds.
* Child becomes an orphan and gets adopted by `init/systemd`.

---

# 4. Zombie Process using fork()

Child terminates first.

### File: q4.c

```c
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if(pid == 0)
    {
        printf("Child Exiting\n");
    }
    else
    {
        sleep(10);

        printf("Parent Exiting\n");
    }

    return 0;
}
```

### Compile

```bash
gcc q4.c -o q4
```

### Run

```bash
./q4
```

### To see zombie

Open another terminal:

```bash
ps -el | grep Z
```

You should see a zombie process during the parent's sleep period.

---

# 5. fork() with Local and Global Variable

### File: q5.c

```c
#include <stdio.h>
#include <unistd.h>

int global = 10;

int main()
{
    int local = 20;

    pid_t pid = fork();

    if(pid == 0)
    {
        global++;
        local++;

        printf("Child Process\n");
        printf("Global = %d\n", global);
        printf("Local = %d\n", local);
    }
    else
    {
        sleep(1);

        printf("Parent Process\n");
        printf("Global = %d\n", global);
        printf("Local = %d\n", local);
    }

    return 0;
}
```

### Compile

```bash
gcc q5.c -o q5
```

### Run

```bash
./q5
```

### Output

```text
Child Process
Global = 11
Local = 21

Parent Process
Global = 10
Local = 20
```

### Viva

Because `fork()` creates a separate address space for the child.

---

# 6. Same Program using vfork()

### File: q6.c

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global = 10;

int main()
{
    int local = 20;

    pid_t pid = vfork();

    if(pid == 0)
    {
        global++;
        local++;

        printf("Child Process\n");
        printf("Global = %d\n", global);
        printf("Local = %d\n", local);

        _exit(0);
    }
    else
    {
        printf("Parent Process\n");
        printf("Global = %d\n", global);
        printf("Local = %d\n", local);
    }

    return 0;
}
```

### Compile

```bash
gcc q6.c -o q6
```

### Run

```bash
./q6
```

### Output

```text
Child Process
Global = 11
Local = 21

Parent Process
Global = 11
Local = 21
```

### Viva

Because `vfork()` temporarily shares the parent's address space, changes made by the child are visible to the parent.
