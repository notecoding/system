// tee.c - 표준 입력을 파일과 표준 출력에 동시에 출력
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp = NULL;     // 출력 파일 포인터
    char buffer[1024];   // 한 줄씩 읽기 위한 버퍼
    int append_mode = 0; // 추가 모드 플래그
    
    // -a 옵션 처리 (파일에 추가 모드)
    int file_index = 1;
    if (argc > 1 && strcmp(argv[1], "-a") == 0) {
        append_mode = 1;  // 추가 모드 활성화
        file_index = 2;   // 파일명 인덱스 조정
    }
    
    // 파일명이 주어진 경우 파일 열기
    if (argc > file_index) {
        // append_mode에 따라 "a"(추가) 또는 "w"(쓰기) 모드로 열기
        fp = fopen(argv[file_index], append_mode ? "a" : "w");
        if (!fp) {
            perror("fopen");
            return 1;
        }
    }
    
    // 표준 입력을 읽어서 표준 출력과 파일에 동시에 출력
    while (fgets(buffer, sizeof(buffer), stdin)) {
        // 표준 출력에 출력 (화면에 표시)
        printf("%s", buffer);
        
        // 파일이 열려있으면 파일에도 출력
        if (fp) {
            fprintf(fp, "%s", buffer);
            fflush(fp);  // 버퍼를 즉시 파일에 쓰기
        }
    }
    
    // 파일이 열려있으면 닫기
    if (fp) {
        fclose(fp);
    }
    
    return 0;
}