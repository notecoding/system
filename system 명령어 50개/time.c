#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    // 명령행 인자 개수 확인 (실행할 명령어가 필요)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct timeval start, end;  // 실시간 측정용
    struct rusage usage;        // 자원 사용량 정보
    
    // 명령어 실행 시작 시간 기록
    gettimeofday(&start, NULL);
    
    // fork로 자식 프로세스 생성
    pid_t pid = fork();
    if (pid == 0) {
        // 자식 프로세스: 주어진 명령어 실행
        execvp(argv[1], &argv[1]);  // argv[1]부터 실행할 명령어와 인자들
        perror("time");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // 부모 프로세스: 자식 프로세스 대기 및 시간 측정
        int status;
        // wait4로 자식 프로세스 종료 대기하면서 자원 사용량 정보도 수집
        wait4(pid, &status, 0, &usage);
        
        // 명령어 실행 종료 시간 기록
        gettimeofday(&end, NULL);
        
        // 실제 경과 시간 계산 (wall clock time)
        double real_time = (end.tv_sec - start.tv_sec) + 
                          (end.tv_usec - start.tv_usec) / 1000000.0;
        // 사용자 CPU 시간 계산
        double user_time = usage.ru_utime.tv_sec + 
                          usage.ru_utime.tv_usec / 1000000.0;
        // 시스템 CPU 시간 계산
        double sys_time = usage.ru_stime.tv_sec + 
                         usage.ru_stime.tv_usec / 1000000.0;
        
        // 시간 정보를 stderr로 출력 (표준 에러)
        fprintf(stderr, "\nreal\t%.3fs\n", real_time);  // 실제 경과 시간
        fprintf(stderr, "user\t%.3fs\n", user_time);    // 사용자 CPU 시간
        fprintf(stderr, "sys\t%.3fs\n", sys_time);      // 시스템 CPU 시간
        
        // 자식 프로세스의 종료 상태 반환
        return WEXITSTATUS(status);
    } else {
        // fork 실패
        perror("fork");
        exit(EXIT_FAILURE);
    }
}