#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *file = stdin;  // 기본적으로 표준 입력에서 읽음
    int hex_mode = 0;    // 16진수 모드 플래그
    int opt;
    
    // getopt로 명령행 옵션 처리
    while ((opt = getopt(argc, argv, "x")) != -1) {
        switch (opt) {
            case 'x':
                hex_mode = 1;  // -x 옵션: 16진수 출력 모드
                break;
            default:
                fprintf(stderr, "Usage: %s [-x] [file]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    // 파일명이 주어진 경우 해당 파일 열기
    if (optind < argc) {
        file = fopen(argv[optind], "rb");  // 바이너리 읽기 모드
        if (!file) {
            perror("od");
            exit(EXIT_FAILURE);
        }
    }
    
    unsigned char buffer[16];  // 16바이트씩 읽기 위한 버퍼
    size_t bytes_read;
    long offset = 0;  // 파일 내 위치(오프셋) 추적
    
    // 파일을 16바이트씩 읽어서 처리
    while ((bytes_read = fread(buffer, 1, 16, file)) > 0) {
        printf("%07lo ", offset);  // 8진수로 오프셋 출력
        
        if (hex_mode) {
            // 16진수 모드: 각 바이트를 16진수로 출력
            for (size_t i = 0; i < bytes_read; i++) {
                printf("%02x ", buffer[i]);
            }
        } else {
            // 기본 모드: 각 바이트를 8진수로 출력
            for (size_t i = 0; i < bytes_read; i++) {
                printf("%03o ", buffer[i]);
            }
        }
        printf("\n");
        offset += bytes_read;  // 오프셋 증가
    }
    // 표준 입력이 아닌 경우에만 파일 닫기
    if (file != stdin) {
        fclose(file);
    }
    return 0;
}