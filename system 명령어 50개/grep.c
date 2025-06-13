// grep - 패턴 검색
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    
    // 패턴과 파일명이 필요
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }
    // 파일 열기
    file = fopen(argv[2], "r");
    if (!file) {
        perror("grep");
        return 1;
    }
    // 파일을 한 줄씩 읽으면서 패턴 검색
    while (fgets(line, sizeof(line), file)) {
        // strstr로 패턴이 포함된 줄인지 확인
        if (strstr(line, argv[1])) {
            printf("%s", line);  // 패턴이 포함된 줄 출력
        }
    }
    fclose(file);
    return 0;
}