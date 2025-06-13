// head - 파일의 처음 몇 줄 출력
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    int count = 10, lines = 0;  // 기본값: 10줄
    
    // 파일명이 필요
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // 파일 열기
    file = fopen(argv[1], "r");
    if (!file) {
        perror("head");
        return 1;
    }
    
    // 파일을 한 줄씩 읽으면서 지정된 줄 수만큼 출력
    while (fgets(line, sizeof(line), file) && lines < count) {
        printf("%s", line);
        lines++;  // 출력한 줄 수 증가
    }
    fclose(file);
    return 0;
}