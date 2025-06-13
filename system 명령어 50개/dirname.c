// dirname.c - 파일 경로에서 디렉토리 경로만 추출
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // 명령행 인자가 정확히 2개인지 확인 (프로그램명 + 경로)
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }
    
    // strdup로 경로 문자열 복사 (원본 수정 방지)
    char *path = strdup(argv[1]);
    // 마지막 '/' 문자의 위치 찾기
    char *last_slash = strrchr(path, '/');
    
    if (last_slash) {
        // '/' 위치에 널 문자 삽입하여 디렉토리 경로만 남김
        *last_slash = '\0';
        printf("%s\n", path);
    } else {
        // '/'가 없으면 현재 디렉토리를 의미하는 "." 출력
        printf(".\n");
    }
    
    free(path);  // strdup으로 할당한 메모리 해제
    return 0;
}