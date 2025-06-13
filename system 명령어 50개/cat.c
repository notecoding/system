// cat - 파일 내용 출력
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char ch;
    
    // 명령행 인수로 파일명이 주어졌는지 확인
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // 파일을 읽기 모드로 열기
    file = fopen(argv[1], "r");
    if (!file) {
        perror("cat");  // 파일 열기 실패 시 에러 메시지 출력
        return 1;
    }
    
    // 파일을 한 문자씩 읽어서 출력
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);  // 읽은 문자를 표준 출력에 출력
    }
    
    fclose(file);  // 파일 닫기
    return 0;
}