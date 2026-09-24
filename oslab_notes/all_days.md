# Day 1: Self-Assessment with General Purpose Utilities in UNIX-like Systems

**1. What is a directory?**
A directory is a location for storing files on your computer.

**2. Significance of HOME variable: The Home Directory.**
The HOME variable stores the absolute path to the current user's home directory.

**3. Operations on directories:**
**a. Check the current directory.**
```bash
pwd
```
**b. Change the current directory.**
```bash
cd /path/to/dir
```
**c. Create new directory (s).**
```bash
mkdir newdir
```
**d. Remove directory (s).**
```bash
rmdir emptydir
```

**4. Absolute pathnames, Relative pathnames.**
Absolute pathnames start from the root `/`, whereas relative pathnames start from the current directory.

**5. What is a command?**
A command is a directive to a computer program to perform a specific task.

**6. What is ls Command?**
`ls` lists directory contents.

**7. How to switch Directories?**
```bash
cd new_directory
```

**8. How to display the user currently working on the system?**
```bash
whoami
```

**9. How to display the name and version of your operating system?**
```bash
uname -a
```

**10. How to display the calendar of a month or year?**
```bash
cal
```

**11. How to display the current system date and time in a variety of formats?**
```bash
date +"%Y-%m-%d %H:%M:%S"
```

**12. How to use echo to display a message on the terminal?**
```bash
echo "Hello"
```

**Handling Ordinary Files: The File System:**

**1. The File. What’s in a (File) name?**
A file is a collection of data. A filename uniquely identifies it within a directory.

**2. Display, create, copy, move, delete, and rename file.**
```bash
cat file.txt
touch newfile.txt
cp file1 file2
mv file1 file2
rm file.txt
mv oldname newname
```

**3. Counting Lines, Words and Characters of file(s).**
```bash
wc file.txt
```

**4. Comparing Two Files.**
```bash
cmp file1 file2
```

**5. What is Common between two files?**
```bash
comm file1 file2
```

**6. Compressing, decompressing and archiving file(s).**
```bash
gzip file.txt
gunzip file.txt.gz
tar -cvf archive.tar file1 file2
```

**Basic File Attributes : File Ownership. File Permissions.**
```bash
chown user file.txt
chmod 755 file.txt
```

**File Filters: Filter Commands: head, tail, cut, sort, uniq, tr, grep, sed.**
```bash
head -n 5 file.txt
tail -n 5 file.txt
cut -d' ' -f1 file.txt
sort file.txt
uniq file.txt
tr 'a-z' 'A-Z' < file.txt
grep "pattern" file.txt
sed 's/old/new/g' file.txt
```

# Day 2: Shell Programming

**1. Write a shell script to calculate addition of two numbers.**
```c
#include <stdio.h>
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", a + b);
    return 0;
}
```

**2. Write a shell script to compare two numbers.**
```c
#include <stdio.h>
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a > b) printf("%d is greater\n", a);
    else if (a < b) printf("%d is greater\n", b);
    else printf("Equal\n");
    return 0;
}
```

**3. Write a shell script to calculate whether a given number is odd or even.**
```c
#include <stdio.h>
int main() {
    int a;
    scanf("%d", &a);
    if (a % 2 == 0) printf("Even\n");
    else printf("Odd\n");
    return 0;
}
```

**4. Write a shell script to calculate the sum of digits of any number entered through the keyboard.**
```c
#include <stdio.h>
int main() {
    int n, s = 0;
    scanf("%d", &n);
    while (n > 0) {
        s += n % 10;
        n /= 10;
    }
    printf("%d\n", s);
    return 0;
}
```

**5. Write a shell script to show the maximum of three numbers.**
```c
#include <stdio.h>
int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (a > b && a > c) printf("%d\n", a);
    else if (b > a && b > c) printf("%d\n", b);
    else printf("%d\n", c);
    return 0;
}
```

**6. Write a shell script which displays the result of division of one integer by another integer and informs if the user tries to divide an integer by 0.**
```c
#include <stdio.h>
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (b == 0) printf("Error: Division by zero\n");
    else printf("%d\n", a / b);
    return 0;
}
```

**7. Write a shell script that takes a number from user and prints the reverse of the number.**
```c
#include <stdio.h>
int main() {
    int n, rev = 0;
    scanf("%d", &n);
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    printf("%d\n", rev);
    return 0;
}
```

**8. Write a shell script to check whether a given number is prime or not.**
```c
#include <stdio.h>
int main() {
    int n, f = 0;
    scanf("%d", &n);
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) { f = 1; break; }
    }
    if (f == 1 || n <= 1) printf("Not Prime\n");
    else printf("Prime\n");
    return 0;
}
```

**9. Write a shell script which displays the message “welcome” and prints the date when you log in to your system.**
```c
#include <stdio.h>
#include <time.h>
int main() {
    printf("welcome\n");
    time_t t = time(NULL);
    printf("%s", ctime(&t));
    return 0;
}
```

**10. Write a shell script which reports names and sizes of all files in a directory whose size exceeds 500 bytes. The filenames should be printed in decreasing order of their sizes. The total number of such files should also be reported.**
```c
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

struct FileInfo { char name[256]; long size; };

int cmp(const void *a, const void *b) {
    return ((struct FileInfo*)b)->size - ((struct FileInfo*)a)->size;
}

int main(int argc, char *argv[]) {
    DIR *d;
    struct dirent *dir;
    struct stat st;
    struct FileInfo files[1000];
    int count = 0;
    
    d = opendir(argv[1]);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            char path[512];
            sprintf(path, "%s/%s", argv[1], dir->d_name);
            stat(path, &st);
            if (S_ISREG(st.st_mode) && st.st_size > 500) {
                strcpy(files[count].name, dir->d_name);
                files[count].size = st.st_size;
                count++;
            }
        }
        closedir(d);
    }
    
    qsort(files, count, sizeof(struct FileInfo), cmp);
    for (int i = 0; i < count; i++) {
        printf("%s %ld\n", files[i].name, files[i].size);
    }
    printf("Total files: %d\n", count);
    return 0;
}
```

**11. Write a shell command that accepts a filename as argument and displays the last modification time, if the file exists and a suitable message if it does not.**
```c
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
int main(int argc, char *argv[]) {
    struct stat st;
    if (stat(argv[1], &st) == 0) {
        printf("Last modified: %s", ctime(&st.st_mtime));
    } else {
        printf("File does not exist\n");
    }
    return 0;
}
```

**12. Write a shell script that accepts two directories namely OS1 and OS2 as arguments and deletes those files in OS2 which are identical to their names in OS1.**
```c
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    DIR *d2 = opendir(argv[2]);
    struct dirent *dir;
    while ((dir = readdir(d2)) != NULL) {
        char path1[512], path2[512];
        sprintf(path1, "%s/%s", argv[1], dir->d_name);
        sprintf(path2, "%s/%s", argv[2], dir->d_name);
        if (access(path1, F_OK) == 0) {
            remove(path2);
        }
    }
    closedir(d2);
    return 0;
}
```

**13. Write a shell script to list the names of files under the current directory started with vowels.**
```c
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
int main() {
    DIR *d = opendir(".");
    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        char c = tolower(dir->d_name[0]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            printf("%s\n", dir->d_name);
        }
    }
    closedir(d);
    return 0;
}
```

**14. Write a shell script to drop the lines which are matched with a given word.**
```c
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[2], "r");
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        if (!strstr(line, argv[1])) {
            printf("%s", line);
        }
    }
    fclose(f);
    return 0;
}
```

**15. Write a shell script that shows the names of all the non-directory files in the current directory and calculates the sum of the size of them.**
```c
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
int main() {
    DIR *d = opendir(".");
    struct dirent *dir;
    struct stat st;
    long sum = 0;
    while ((dir = readdir(d)) != NULL) {
        stat(dir->d_name, &st);
        if (S_ISREG(st.st_mode)) {
            printf("%s\n", dir->d_name);
            sum += st.st_size;
        }
    }
    printf("Total size: %ld\n", sum);
    closedir(d);
    return 0;
}
```

**16. Write a shell script to find the total number of words, characters, lines in the given file (name of the file given in command line argument).**
```c
#include <stdio.h>
#include <ctype.h>
int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    int c, chars = 0, words = 0, lines = 0, in_word = 0;
    while ((c = fgetc(f)) != EOF) {
        chars++;
        if (c == '\n') lines++;
        if (isspace(c)) in_word = 0;
        else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    fclose(f);
    printf("Lines: %d Words: %d Chars: %d\n", lines, words, chars);
    return 0;
}
```

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

# Day 5: Threads-1

**1. Write a program to create a thread that displays a WELCOME message.**
```c
#include <stdio.h>
#include <pthread.h>
void* msg(void* arg) {
    printf("WELCOME\n");
    return NULL;
}
int main() {
    pthread_t t;
    pthread_create(&t, NULL, msg, NULL);
    pthread_join(t, NULL);
    return 0;
}
```

**2. Write a program that creates multiple threads and terminate those. The program should create 5 threads with the pthread_create() routine. Each thread prints a “Hello World!” message and then terminates with a call to pthread_exit().**
```c
#include <stdio.h>
#include <pthread.h>
void* msg(void* arg) {
    printf("Hello World!\n");
    pthread_exit(NULL);
}
int main() {
    pthread_t t[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&t[i], NULL, msg, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}
```

**3. Write a program which implements thread with arguments and thread joining.**
```c
#include <stdio.h>
#include <pthread.h>
void* msg(void* arg) {
    int val = *(int*)arg;
    printf("Argument: %d\n", val);
    return NULL;
}
int main() {
    pthread_t t;
    int arg = 10;
    pthread_create(&t, NULL, msg, &arg);
    pthread_join(t, NULL);
    return 0;
}
```

# Day 6: Threads-2

**1. Write a multi-threaded program where the main thread gets an integer number range from the user and then creates two child threads; one thread finds odd numbers in the range and print them, and the second thread finds even numbers in the range and prints them. The child thread must terminate by returning a value. The parent thread must wait for the child threads to finish and it must also print the return values of the child threads.**
```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct Range { int start, end; };
void* odd(void* arg) {
    struct Range* r = (struct Range*)arg;
    for (int i = r->start; i <= r->end; i++) {
        if (i % 2 != 0) printf("Odd: %d\n", i);
    }
    return (void*)1;
}
void* even(void* arg) {
    struct Range* r = (struct Range*)arg;
    for (int i = r->start; i <= r->end; i++) {
        if (i % 2 == 0) printf("Even: %d\n", i);
    }
    return (void*)2;
}
int main() {
    pthread_t t1, t2;
    struct Range r;
    scanf("%d %d", &r.start, &r.end);
    pthread_create(&t1, NULL, odd, &r);
    pthread_create(&t2, NULL, even, &r);
    void *ret1, *ret2;
    pthread_join(t1, &ret1);
    pthread_join(t2, &ret2);
    printf("Ret1: %ld, Ret2: %ld\n", (long)ret1, (long)ret2);
    return 0;
}
```

**2. Write a multi-threaded program where the main thread gets an integer number range from the user and then creates two child threads; one thread calculates the sum of all numbers in the range and prints it, and the second thread finds prime numbers in the range and prints them. The child thread must terminate by returning a value. The parent thread must wait for the child threads to finish, and it must also print the return values of the child threads.**
```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
struct Range { int start, end; };
void* sum(void* arg) {
    struct Range* r = (struct Range*)arg;
    long s = 0;
    for (int i = r->start; i <= r->end; i++) s += i;
    printf("Sum: %ld\n", s);
    return (void*)1;
}
void* prime(void* arg) {
    struct Range* r = (struct Range*)arg;
    for (int i = r->start; i <= r->end; i++) {
        int f = 0;
        for (int j = 2; j <= i/2; j++) {
            if (i % j == 0) { f = 1; break; }
        }
        if (f == 0 && i > 1) printf("Prime: %d\n", i);
    }
    return (void*)2;
}
int main() {
    pthread_t t1, t2;
    struct Range r;
    scanf("%d %d", &r.start, &r.end);
    pthread_create(&t1, NULL, sum, &r);
    pthread_create(&t2, NULL, prime, &r);
    void *ret1, *ret2;
    pthread_join(t1, &ret1);
    pthread_join(t2, &ret2);
    printf("Ret1: %ld, Ret2: %ld\n", (long)ret1, (long)ret2);
    return 0;
}
```

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

# Day 10: Deadlock

**1. Implement Banker’s algorithm.**
```c
#include <stdio.h>
int main() {
    int n = 5, m = 3;
    int alloc[5][3] = {{0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2}};
    int max[5][3] = {{7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3}};
    int avail[3] = {3,3,2}, need[5][3], f[5] = {0}, ans[5], ind = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) { flag = 1; break; }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) avail[y] += alloc[i][y];
                    f[i] = 1;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
```
