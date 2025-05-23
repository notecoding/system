#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main(void) {
    int pid, child, status;
    printf("[%d] 부모 프로세스 시작\n", getpid());

    pid = fork();
    if (pid == 0) {
        // 자식 프로세스
        printf("[%d] 자식 프로세스 시작\n", getpid());
        exit(1);
    }

    // 부모 프로세스
    child = wait(&status); // 자식 프로세스가 끝나기를 기다림
    printf("[%d] 자식 프로세스 %d 종료\n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);

    return 0;
}
