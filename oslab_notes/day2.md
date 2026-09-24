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
