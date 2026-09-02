#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Process 2 started with PID: %d\n", getpid());
    printf("This is a demo process 2 program.\n");
    return 0;
}
