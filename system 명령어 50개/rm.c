// rm - 파일 삭제
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // 명령행 인자 개수 확인 (프로그램명 + 파일명)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // unlink 시스템 콜로 파일 삭제
    // unlink는 파일의 링크를 제거하여 파일을 삭제함
    if (unlink(argv[1]) == -1) {
        perror("rm");  // 실패 시 시스템 에러 메시지 출력
        return 1;
    }
    
    return 0;
}