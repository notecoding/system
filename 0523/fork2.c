#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 부모 프로세스가 자식 프로세스를 생성하고 서로 다른 메시지를 출력 */
int main(void) {
    int pid;
    pid = fork();

    if (pid == 0) {   // 자식 프로세스
        printf("[Child] : Hello, world pid=%d\n", getpid());
        exit(0);
    } else {          // 부모 프로세스
        printf("[Parent] : Hello, world pid=%d\n", getpid());
    }

    return 0;
}
