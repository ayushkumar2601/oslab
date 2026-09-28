# Operating System Concepts Lab (IOT3152) Assignment

## 1 Self-Assessment with General Purpose Utilities in UNIX-like Systems

**1. What is a directory?**
A directory is a location for storing files on your computer. In UNIX, a directory is a type of file that contains a list of other files and directories.

**2. Significance of HOME variable: The Home Directory.**
The `$HOME` variable points to the current user's default login directory. It is where a user's personal files and configuration are stored.

**3. Operations on directories:**
a. **Check the current directory:** `pwd`
b. **Change the current directory:** `cd <path>`
c. **Create new directory(s):** `mkdir <directory_name>`
d. **Remove directory(s):** `rmdir <directory_name>` (for empty directories) or `rm -r <directory_name>` (for non-empty).

**4. Absolute pathnames, Relative pathnames.**
- Absolute path: The full path to a file or directory starting from the root directory `/`. (e.g., `/home/user/Desktop`)
- Relative path: The path to a file or directory starting from the current working directory. (e.g., `./Desktop`)

**5. What is a command?**
A command is an instruction given to the computer's shell to perform a specific task or program.

**6. What is ls Command?**
The `ls` command is used to list the contents (files and directories) of a directory.

**7. How to switch Directories?**
Using the `cd` (change directory) command. Example: `cd /var/log`.

**8. How to display the user currently working on the system?**
Run `whoami` or `who`.

**9. How to display the name and version of your operating system?**
Run `uname -a`.

**10. How to display the calendar of a month or year?**
Run `cal` for the current month, or `cal 2024` for the year 2024.

**11. How to display the current system date and time in a variety of formats?**
Run `date` (default format) or `date "+%Y-%m-%d %H:%M:%S"` (custom format).

**12. How to use echo to display a message on the terminal?**
Run `echo "Your message here"`.

### Handling Ordinary Files
1. **The File. What’s in a (File) name?** A file is a container for data. A filename is a unique identifier within a directory.
2. **Commands:**
   - Display: `cat <file>`
   - Create: `touch <file>`
   - Copy: `cp <src> <dest>`
   - Move: `mv <src> <dest>`
   - Delete: `rm <file>`
   - Rename: `mv <old_name> <new_name>`
3. **Counting Lines, Words, and Characters:** `wc <file>`
4. **Comparing Two Files:** `cmp file1 file2` or `diff file1 file2`
5. **What is Common between two files:** `comm file1 file2`
6. **Compressing, decompressing, and archiving:**
   - Compress: `gzip <file>`
   - Decompress: `gunzip <file.gz>`
   - Archive: `tar -cvf archive.tar <folder>`

### Basic File Attributes
- **Ownership:** `chown user:group <file>`
- **Permissions:** `chmod 755 <file>`

### File Filters
- `head`: Display first N lines.
- `tail`: Display last N lines.
- `cut`: Remove sections from lines.
- `sort`: Sort lines of text files.
- `uniq`: Report or omit repeated lines.
- `tr`: Translate or delete characters.
- `grep`: Print lines matching a pattern.
- `sed`: Stream editor for filtering and transforming text.

---

## 2 Shell Programming

*To run these shell scripts: Save the code in a file (e.g., `script.sh`), make it executable using `chmod +x script.sh`, and run it using `./script.sh`.*

**1. Calculate addition of two numbers.**
```bash
#!/bin/bash
read -p "Enter two numbers: " a b
echo "Sum is: $((a + b))"
```

**2. Compare two numbers.**
```bash
#!/bin/bash
read -p "Enter two numbers: " a b
if [ $a -gt $b ]; then
    echo "$a is greater than $b"
elif [ $a -lt $b ]; then
    echo "$b is greater than $a"
else
    echo "Both are equal"
fi
```

**3. Calculate whether a given number is odd or even.**
```bash
#!/bin/bash
read -p "Enter a number: " n
if [ $((n % 2)) -eq 0 ]; then
    echo "Even"
else
    echo "Odd"
fi
```

**4. Calculate the sum of digits of any number.**
```bash
#!/bin/bash
read -p "Enter a number: " n
sum=0
while [ $n -gt 0 ]; do
    rem=$((n % 10))
    sum=$((sum + rem))
    n=$((n / 10))
done
echo "Sum of digits is: $sum"
```

**5. Show the maximum of three numbers.**
```bash
#!/bin/bash
read -p "Enter three numbers: " a b c
max=$a
if [ $b -gt $max ]; then max=$b; fi
if [ $c -gt $max ]; then max=$c; fi
echo "Maximum is: $max"
```

**6. Division with divide by 0 check.**
```bash
#!/bin/bash
read -p "Enter two numbers (dividend divisor): " a b
if [ $b -eq 0 ]; then
    echo "Error: Cannot divide by zero!"
else
    echo "Result is: $(echo "scale=2; $a / $b" | bc)"
fi
```

**7. Reverse of a number.**
```bash
#!/bin/bash
read -p "Enter a number: " n
rev=0
while [ $n -gt 0 ]; do
    rem=$((n % 10))
    rev=$((rev * 10 + rem))
    n=$((n / 10))
done
echo "Reverse is: $rev"
```

**8. Check whether a given number is prime or not.**
```bash
#!/bin/bash
read -p "Enter a number: " n
if [ $n -lt 2 ]; then echo "Not prime"; exit; fi
for ((i=2; i*i<=n; i++)); do
    if [ $((n % i)) -eq 0 ]; then
        echo "Not prime"
        exit
    fi
done
echo "Prime"
```

**9. Display “welcome” and login date.**
```bash
#!/bin/bash
echo "Welcome $USER"
echo "You logged in at: $(date)"
```

**10. Files exceeding 500 bytes.**
```bash
#!/bin/bash
if [ -z "$1" ]; then echo "Provide directory as argument"; exit 1; fi
echo "Files > 500 bytes (decreasing order):"
find "$1" -type f -size +500c -exec ls -l {} + | awk '{print $5, $9}' | sort -nr
count=$(find "$1" -type f -size +500c | wc -l)
echo "Total number of such files: $count"
```

**11. Last modification time.**
```bash
#!/bin/bash
if [ -z "$1" ]; then echo "Provide filename"; exit 1; fi
if [ -e "$1" ]; then
    stat -c "Last modified: %y" "$1"
else
    echo "File does not exist"
fi
```

**12. Delete identical files in OS2 as OS1.**
```bash
#!/bin/bash
if [ "$#" -ne 2 ]; then echo "Provide two directories (OS1 OS2)"; exit 1; fi
dir1=$1; dir2=$2
for file in $(ls "$dir1"); do
    if [ -f "$dir2/$file" ]; then
        if cmp -s "$dir1/$file" "$dir2/$file"; then
            rm "$dir2/$file"
            echo "Deleted $dir2/$file"
        fi
    fi
done
```

**13. List names of files starting with vowels.**
```bash
#!/bin/bash
ls | grep -i '^[aeiou]'
```

**14. Drop lines matched with a given word.**
```bash
#!/bin/bash
read -p "Enter filename and word: " file word
grep -v "$word" "$file"
```

**15. Non-directory files sum of size.**
```bash
#!/bin/bash
sum=0
for file in $(find . -maxdepth 1 -type f); do
    size=$(stat -c "%s" "$file")
    sum=$((sum + size))
done
echo "Total size of non-directory files: $sum bytes"
```

**16. Total words, characters, lines.**
```bash
#!/bin/bash
if [ -z "$1" ]; then echo "Provide filename"; exit 1; fi
wc "$1"
```

---

## Instructions for Running C Programs
Save the code in a file named `program.c`.
- **Compile:** `gcc program.c -o program -lpthread`
- **Run:** `./program`

---

## 3 Process-1

**1. Creation of a process.**
```c
#include <stdio.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) printf("Child Process\n");
    else if (pid > 0) printf("Parent Process\n");
    return 0;
}
```

**2. PID of parent and child process.**
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
#include <stdlib.h>
int main() {
    pid_t pid = fork();
    if (pid > 0) {
        printf("Parent process terminating...\n");
        exit(0);
    } else if (pid == 0) {
        sleep(2);
        printf("Child (Orphan) PID: %d, New Parent PID: %d\n", getpid(), getppid());
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
        printf("Parent sleeping... Check 'ps' for zombie process [Z+]\n");
        sleep(10);
    } else if (pid == 0) {
        printf("Child process terminating to become a zombie\n");
        exit(0);
    }
    return 0;
}
```

**5. Fork with local and global variables.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int global_var = 10;
int main() {
    int local_var = 20;
    pid_t pid = fork();
    if (pid == 0) {
        global_var++; local_var++;
        printf("Child - Global: %d, Local: %d\n", global_var, local_var);
    } else {
        wait(NULL);
        printf("Parent - Global: %d, Local: %d\n", global_var, local_var);
    }
    return 0;
}
```

**6. Fork with local and global variables using vfork.**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int global_var = 10;
int main() {
    int local_var = 20;
    pid_t pid = vfork();
    if (pid == 0) {
        global_var++; local_var++;
        printf("Child - Global: %d, Local: %d\n", global_var, local_var);
        _exit(0);
    } else {
        printf("Parent - Global: %d, Local: %d\n", global_var, local_var);
    }
    return 0;
}
```

---

## 4 Process-2

**1. Three child processes with exec functions.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
    if (fork() == 0) { execlp("who", "who", NULL); exit(0); }
    if (fork() == 0) { execlp("ls", "ls", "-al", NULL); exit(0); }
    if (fork() == 0) { execl("/bin/date", "date", NULL); exit(0); }
    
    int status;
    for (int i = 0; i < 3; i++) {
        wait(&status);
        printf("A Child finished with status %d\n", WEXITSTATUS(status));
    }
    return 0;
}
```

**2. Background process for fifty seconds.**
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
    printf("Background process started with PID: %d\n", pid);
    return 0;
}
```

**3. Two child processes print 1 to 10.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            for (int j = 1; j <= 10; j++) {
                printf("Child %d (PID: %d, PPID: %d): %d\n", i+1, getpid(), getppid(), j);
            }
            exit(0);
        }
    }
    wait(NULL);
    wait(NULL);
    printf("Good Bye\n");
    return 0;
}
```

---

## 5 Threads-1

**1. Create a thread that displays a WELCOME message.**
```c
#include <stdio.h>
#include <pthread.h>
void* print_msg(void* arg) {
    printf("WELCOME\n");
    return NULL;
}
int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, print_msg, NULL);
    pthread_join(thread, NULL);
    return 0;
}
```

**2. 5 threads Hello World! and exit.**
```c
#include <stdio.h>
#include <pthread.h>
void* print_hello(void* arg) {
    long tid = (long)arg;
    printf("Hello World! from thread %ld\n", tid);
    pthread_exit(NULL);
}
int main() {
    pthread_t threads[5];
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, print_hello, (void*)i);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
```

**3. Thread with arguments and joining.**
```c
#include <stdio.h>
#include <pthread.h>
void* square(void* arg) {
    int num = *(int*)arg;
    printf("Square of %d is %d\n", num, num * num);
    return NULL;
}
int main() {
    pthread_t thread;
    int val = 5;
    pthread_create(&thread, NULL, square, &val);
    pthread_join(thread, NULL);
    return 0;
}
```

---

## 6 Threads-2

**1. Odd and even numbers in a range.**
```c
#include <stdio.h>
#include <pthread.h>

struct Range { int start, end; };

void* print_odd(void* arg) {
    struct Range* r = (struct Range*)arg;
    long count = 0;
    for (int i = r->start; i <= r->end; i++) {
        if (i % 2 != 0) { printf("Odd: %d\n", i); count++; }
    }
    return (void*)count;
}

void* print_even(void* arg) {
    struct Range* r = (struct Range*)arg;
    long count = 0;
    for (int i = r->start; i <= r->end; i++) {
        if (i % 2 == 0) { printf("Even: %d\n", i); count++; }
    }
    return (void*)count;
}

int main() {
    int start, end;
    printf("Enter range (start end): ");
    scanf("%d %d", &start, &end);
    struct Range r = {start, end};

    pthread_t t1, t2;
    pthread_create(&t1, NULL, print_odd, &r);
    pthread_create(&t2, NULL, print_even, &r);

    void *r1, *r2;
    pthread_join(t1, &r1);
    pthread_join(t2, &r2);

    printf("Total Odd numbers: %ld\n", (long)r1);
    printf("Total Even numbers: %ld\n", (long)r2);
    return 0;
}
```

**2. Sum and prime numbers in a range.**
```c
#include <stdio.h>
#include <pthread.h>

struct Range { int start, end; };

void* calc_sum(void* arg) {
    struct Range* r = (struct Range*)arg;
    long sum = 0;
    for (int i = r->start; i <= r->end; i++) sum += i;
    return (void*)sum;
}

void* print_prime(void* arg) {
    struct Range* r = (struct Range*)arg;
    long count = 0;
    for (int i = r->start; i <= r->end; i++) {
        if (i < 2) continue;
        int is_prime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) { is_prime = 0; break; }
        }
        if (is_prime) { printf("Prime: %d\n", i); count++; }
    }
    return (void*)count;
}

int main() {
    int start, end;
    printf("Enter range (start end): ");
    scanf("%d %d", &start, &end);
    struct Range r = {start, end};

    pthread_t t1, t2;
    pthread_create(&t1, NULL, calc_sum, &r);
    pthread_create(&t2, NULL, print_prime, &r);

    void *sum, *primes;
    pthread_join(t1, &sum);
    pthread_join(t2, &primes);

    printf("Sum: %ld\n", (long)sum);
    printf("Total Prime numbers: %ld\n", (long)primes);
    return 0;
}
```

---

## 7 Signals

**1. Catch SIGCHLD signal.**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int sig) {
    printf("Caught SIGCHLD from terminated child.\n");
}

int main() {
    signal(SIGCHLD, handler);
    if (fork() == 0) {
        printf("Child process running...\n");
        exit(0);
    }
    wait(NULL);
    return 0;
}
```

**2. Default message of SIGINT.**
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("\nInterrupt signal caught (SIGINT).\nUser: %s\n", getenv("USER"));
    exit(0);
}

int main() {
    signal(SIGINT, handler);
    printf("Running. Press Ctrl+C...\n");
    while(1) sleep(1);
    return 0;
}
```

**3. Process cannot be killed by Ctrl+C and restore.**
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("Ignoring SIGINT. Press Ctrl+C, nothing will happen.\n");
    signal(SIGINT, SIG_IGN);
    sleep(5);
    
    printf("Restoring SIGINT. Press Ctrl+C to exit.\n");
    signal(SIGINT, SIG_DFL);
    sleep(5);
    return 0;
}
```

**4. SIGUSR1 and SIGUSR2.**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) {
    printf("I am awake\n");
    exit(0);
}

int main() {
    pid_t a = fork();
    if (a == 0) {
        signal(SIGUSR1, handler);
        while(1) pause();
    }
    
    pid_t b = fork();
    if (b == 0) {
        signal(SIGUSR2, handler);
        while(1) pause();
    }
    
    sleep(1);
    kill(a, SIGUSR1);
    kill(b, SIGUSR2);
    return 0;
}
```

**5. Value of delay as command line argument.**
*Run as: `./program 3`*
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    int delay = atoi(argv[1]);

    pid_t pid = fork();
    if (pid == 0) {
        sleep(5); // Child takes 5 seconds
        exit(42);
    }

    int status;
    for (int i = 0; i < delay; i++) {
        sleep(1);
        int w = waitpid(pid, &status, WNOHANG);
        if (w == pid) {
            printf("Child %d finished with status %d\n", pid, WEXITSTATUS(status));
            return 0;
        }
    }
    
    printf("Child %d exceeded time, killing...\n", pid);
    kill(pid, SIGKILL);
    return 0;
}
```

---

## 8 Inter-process Communication – Pipes

**1. Process communicates with another using `pipe`.**
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        close(fd[0]);
        char msg[] = "Hello from child";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    } else {
        close(fd[1]);
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent read: %s\n", buffer);
        close(fd[0]);
    }
    return 0;
}
```

**2. Process communicates using `popen`.**
```c
#include <stdio.h>

int main() {
    FILE *fp = popen("ls -l", "r");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    pclose(fp);
    return 0;
}
```

**3. One-way pipe to reverse string.**
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}

int main() {
    int fd[2];
    pipe(fd);
    
    if (fork() == 0) {
        close(fd[1]);
        char buffer[100];
        while (1) {
            read(fd[0], buffer, sizeof(buffer));
            if (strcmp(buffer, "quit") == 0) break;
            reverse(buffer);
            printf("Child reversed: %s\n", buffer);
        }
        close(fd[0]);
        exit(0);
    } else {
        close(fd[0]);
        char str[100];
        while (1) {
            printf("Enter string (type 'quit' to exit): ");
            scanf("%s", str);
            write(fd[1], str, strlen(str) + 1);
            if (strcmp(str, "quit") == 0) break;
            sleep(1);
        }
        close(fd[1]);
    }
    return 0;
}
```

**4. Two-way pipe for integer sum.**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int p1[2], p2[2];
    pipe(p1); pipe(p2);
    
    if (fork() == 0) {
        close(p1[1]); close(p2[0]);
        int n;
        while (1) {
            read(p1[0], &n, sizeof(n));
            if (n == 0) break;
            int sum = n * (n + 1) / 2;
            write(p2[1], &sum, sizeof(sum));
        }
        close(p1[0]); close(p2[1]);
        exit(0);
    } else {
        close(p1[0]); close(p2[1]);
        int n, sum;
        while (1) {
            printf("Enter integer (0 to exit): ");
            scanf("%d", &n);
            write(p1[1], &n, sizeof(n));
            if (n == 0) break;
            read(p2[0], &sum, sizeof(sum));
            printf("Sum up to %d is %d\n", n, sum);
        }
        close(p1[1]); close(p2[0]);
    }
    return 0;
}
```

**5. One-way pipe: Divide range for prime search.**
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void print_primes(int start, int end, int child_num) {
    for (int i = start; i <= end; i++) {
        if (i < 2) continue;
        int is_prime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) { is_prime = 0; break; }
        }
        if (is_prime) printf("Child %d Prime: %d\n", child_num, i);
    }
}

int main() {
    int fd[3][2];
    int start, end;
    printf("Enter range (start end): ");
    scanf("%d %d", &start, &end);
    
    int range = (end - start + 1) / 3;
    
    for (int i = 0; i < 3; i++) {
        pipe(fd[i]);
        if (fork() == 0) {
            close(fd[i][1]);
            int limits[2];
            read(fd[i][0], limits, sizeof(limits));
            print_primes(limits[0], limits[1], i + 1);
            close(fd[i][0]);
            exit(0);
        }
        close(fd[i][0]);
    }
    
    for (int i = 0; i < 3; i++) {
        int limits[2];
        limits[0] = start + i * range;
        limits[1] = (i == 2) ? end : start + (i + 1) * range - 1;
        write(fd[i][1], limits, sizeof(limits));
        close(fd[i][1]);
    }
    
    for (int i = 0; i < 3; i++) wait(NULL);
    return 0;
}
```

---

## 9 Semaphores

**1. Producer consumer problem (single piece of data).**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buffer;
sem_t empty, full;

void* producer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&empty);
        buffer = i;
        printf("Produced: %d\n", buffer);
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&full);
        printf("Consumed: %d\n", buffer);
        sem_post(&empty);
    }
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
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
```

**2. Producer consumer problem (two consumers).**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buffer;
sem_t empty, full;

void* producer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        buffer = i;
        printf("Produced: %d\n", buffer);
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    long id = (long)arg;
    for (int i = 1; i <= 5; i++) { // Each consumes 5 items (Total 10)
        sem_wait(&full);
        printf("Consumer %ld consumed: %d\n", id, buffer);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t p, c1, c2;
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c1, NULL, consumer, (void*)1);
    pthread_create(&c2, NULL, consumer, (void*)2);
    pthread_join(p, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
```

**3. Producer consumer problem (bounded length array).**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void* producer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = i;
        printf("Produced: %d\n", i);
        in = (in + 1) % SIZE;
        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;
        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t p, c;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);
    
    return 0;
}
```

**4. Pthread condition variable routines (wait till count 500).**
```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void* inc_count(void* id) {
    for (int i = 0; i < 300; i++) {
        pthread_mutex_lock(&count_mutex);
        count++;
        if (count == 500) {
            pthread_cond_signal(&count_threshold_cv);
        }
        pthread_mutex_unlock(&count_mutex);
    }
    return NULL;
}

void* watch_count(void* id) {
    pthread_mutex_lock(&count_mutex);
    while (count < 500) {
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
    }
    printf("Threshold 500 reached! count = %d\n", count);
    pthread_mutex_unlock(&count_mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold_cv, NULL);
    
    pthread_create(&t3, NULL, watch_count, NULL);
    pthread_create(&t1, NULL, inc_count, NULL);
    pthread_create(&t2, NULL, inc_count, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);
    return 0;
}
```

**5. Dining Philosophers problem.**
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopsticks[5];

void* philosopher(void* num) {
    int id = *(int*)num;
    sem_wait(&chopsticks[id]);
    sem_wait(&chopsticks[(id + 1) % 5]);
    printf("Philosopher %d is eating\n", id);
    sleep(1);
    sem_post(&chopsticks[id]);
    sem_post(&chopsticks[(id + 1) % 5]);
    printf("Philosopher %d finished eating\n", id);
    return NULL;
}

int main() {
    pthread_t phils[5];
    int ids[5];
    for (int i = 0; i < 5; i++) sem_init(&chopsticks[i], 0, 1);
    for (int i = 0; i < 5; i++) { 
        ids[i] = i; 
        pthread_create(&phils[i], NULL, philosopher, &ids[i]); 
    }
    for (int i = 0; i < 5; i++) pthread_join(phils[i], NULL);
    return 0;
}
```

---

## 10 Deadlock

**1. Banker’s algorithm.**
```c
#include <stdio.h>

int main() {
    int n, m, i, j, k;
    n = 5; // Processes
    m = 3; // Resources
    
    // Allocation Matrix
    int alloc[5][3] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };
    
    // MAX Matrix
    int max[5][3] = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };
    
    // Available Resources
    int avail[3] = {3, 3, 2}; 

    int f[5], ans[5], ind = 0;
    for (k = 0; k < n; k++) f[k] = 0;
    
    int need[5][3];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int y = 0;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) { flag = 1; break; }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (y = 0; y < m; y++) avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }

    printf("Safe Sequence is: \n");
    for (i = 0; i < n - 1; i++) printf("P%d -> ", ans[i]);
    printf("P%d\n", ans[n - 1]);

    return 0;
}
```
