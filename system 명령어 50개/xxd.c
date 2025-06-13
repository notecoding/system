#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *file = stdin; // 기본적으로 표준 입력 사용
    
    // 파일명이 주어지면 해당 파일을 열음
    if (argc > 1) {
        file = fopen(argv[1], "rb"); // "rb": 바이너리 읽기 모드
        if (!file) {
            perror("xxd");
            exit(EXIT_FAILURE);
        }
    }
    
    unsigned char buffer[16]; // 한 번에 16바이트씩 읽어서 처리
    size_t bytes_read;
    long offset = 0; // 파일에서의 현재 위치(오프셋)
    
    // 16바이트씩 읽어서 hex dump 형식으로 출력
    while ((bytes_read = fread(buffer, 1, 16, file)) > 0) {
        printf("%08lx: ", offset); // 오프셋을 8자리 16진수로 출력
        
        // 16바이트를 2자리 16진수로 출력 (hex 부분)
        for (size_t i = 0; i < 16; i++) {
            if (i < bytes_read) {
                printf("%02x", buffer[i]); // 2자리 16진수로 출력
            } else {
                printf("  "); // 데이터가 없으면 공백
            }
            if (i % 2 == 1) printf(" "); // 2바이트마다 공백 추가
        }
        
        printf(" ");
        
        // ASCII 표현 부분 출력
        for (size_t i = 0; i < bytes_read; i++) {
            // 출력 가능한 문자면 그대로, 아니면 '.'으로 표시
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }
        
        printf("\n");
        offset += bytes_read; // 다음 줄을 위해 오프셋 증가
    }
    
    // 표준 입력이 아닌 경우에만 파일 닫기
    if (file != stdin) {
        fclose(file);
    }
    
    return 0;
}