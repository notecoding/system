// mv - 파일 이동/이름변경
#include <stdio.h>

int main(int argc, char *argv[]) {
    // 명령행 인자 개수 확인 (프로그램명 + 소스 + 목적지)
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    
    // rename 시스템 콜로 파일 이동/이름 변경
    // argv[1]: 원본 파일/디렉토리, argv[2]: 목적지 파일/디렉토리
    if (rename(argv[1], argv[2]) == -1) {
        perror("mv");  // 실패 시 시스템 에러 메시지 출력
        return 1;
    }
    
    return 0;
}