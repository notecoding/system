// pwd - 현재 작업 디렉토리 출력
#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];  // 현재 작업 디렉토리 경로를 저장할 버퍼
    
    // getcwd로 현재 작업 디렉토리 경로 획득
    if (getcwd(cwd, sizeof(cwd))) {
        printf("%s\n", cwd);  // 경로 출력
    } else {
        perror("pwd");  // 실패 시 에러 메시지 출력
        return 1;
    }
    return 0;
}