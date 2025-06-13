// sleep - 지정된 시간만큼 대기
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // 명령행 인자 개수 확인 (프로그램명 + 초)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <seconds>\n", argv[0]);
        return 1;
    }
    
    // 문자열을 정수로 변환하여 대기 시간 설정
    unsigned int seconds = atoi(argv[1]);
    sleep(seconds);  // 지정된 초만큼 프로세스 대기
    
    return 0;
}