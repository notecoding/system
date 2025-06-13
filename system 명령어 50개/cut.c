// cut - 텍스트 필드 추출
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024], *token;
    int field = 1;
    
    // 필드 번호와 파일명이 필요
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <field_number> <filename>\n", argv[0]);
        return 1;
    }
    
    field = atoi(argv[1]);  // 추출할 필드 번호
    // 파일을 읽기 모드로 열기
    file = fopen(argv[2], "r");
    if (!file) {
        perror("cut");
        return 1;
    }
    
    // 파일을 한 줄씩 읽기
    while (fgets(line, sizeof(line), file)) {
        // 공백과 탭으로 첫 번째 토큰 분리
        token = strtok(line, " \t");
        // 지정된 필드까지 토큰 이동
        for (int i = 1; i < field && token; i++) {
            token = strtok(NULL, " \t");  // 다음 토큰 가져오기
        }
        // 해당 필드가 존재하면 출력
        if (token) {
            printf("%s", token);
        }
        printf("\n");
    }
    
    fclose(file);
    return 0;
}