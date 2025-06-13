// mkdir - 디렉토리 생성
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // 명령행 인자 개수 확인 (프로그램명 + 디렉토리명)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    
    // mkdir 시스템 콜로 디렉토리 생성
    // 0755: 소유자(rwx), 그룹(rx), 기타(rx) 권한 설정
    if (mkdir(argv[1], 0755) == -1) {
        perror("mkdir");  // 실패 시 시스템 에러 메시지 출력
        return 1;
    }
    
    return 0;
}