#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* 부모 프로세스가 두 개의 자식 프로세스를 생성한다 */
int main(void) {
    int pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        printf("[Child 1] : Hello, world! pid=%d\n", getpid());
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("[Child 2] : Hello, world! pid=%d\n", getpid());
        exit(0);
    }

    printf("[PARENT] : Hello, world! pid=%d\n", getpid());

    // 자식들이 종료될 때까지 기다림
    wait(NULL);
    wait(NULL);

    return 0;
}
