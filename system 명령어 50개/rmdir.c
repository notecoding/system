// rmdir - 빈 디렉토리 삭제
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // 명령행 인자 개수 확인 (프로그램명 + 디렉토리명)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    
    // rmdir 시스템 콜로 빈 디렉토리 삭제
    // 디렉토리가 비어있지 않으면 삭제 실패
    if (rmdir(argv[1]) == -1) {
        perror("rmdir");  // 실패 시 시스템 에러 메시지 출력
        return 1;
    }
    
    return 0;
}