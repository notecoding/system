#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 자식 프로세스를 생성한다. */
int main(void) {
    int pid;
    printf("[%d] 프로세스 시작\n", getpid());

    pid = fork();

    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);

    return 0;
}
