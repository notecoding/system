// uniq - 중복 줄 제거
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
    FILE *file;
    char current[1024], previous[1024] = ""; // 현재 줄과 이전 줄을 저장할 버퍼
    
    // 파일명이 인자로 주어져야 함
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    file = fopen(argv[1], "r");
    if (!file) {
        perror("uniq");
        return 1;
    }
    // 파일에서 한 줄씩 읽어서 처리
    while (fgets(current, sizeof(current), file)) {
        // 현재 줄이 이전 줄과 다르면 출력 (연속된 중복 줄만 제거)
        if (strcmp(current, previous) != 0) {
            printf("%s", current);
            strcpy(previous, current); // 현재 줄을 이전 줄로 저장
        }
    }
    fclose(file);
    return 0;
}