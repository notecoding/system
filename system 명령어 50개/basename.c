// basename.c - 파일 경로에서 파일명만 추출
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // 명령행 인자가 정확히 2개인지 확인 (프로그램명 + 경로)
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return 1;
    }
    
    char *path = argv[1];  // 첫 번째 인자(경로)를 path 변수에 저장
    
    // strrchr로 경로에서 마지막 '/' 문자의 위치를 찾음
    // 리눅스/유닉스에서 디렉토리 구분자는 '/'
    char *base = strrchr(path, '/');
    
    // '/'가 발견되었다면 (즉, 경로에 디렉토리가 포함되어 있다면)
    if (base) {
        // base + 1: '/' 다음 문자부터 출력 (파일명만 출력)
        printf("%s\n", base + 1);
    } else {
        // '/'가 없다면 전체 경로가 파일명이므로 그대로 출력
        printf("%s\n", path);
    }
    
    return 0;
}