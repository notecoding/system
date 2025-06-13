// cp - 파일 복사
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *src, *dst;
    char ch;
    
    // 소스 파일과 대상 파일 이름이 모두 필요
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    
    // 소스 파일을 읽기 모드로 열기
    src = fopen(argv[1], "r");
    if (!src) {
        perror("cp: source");
        return 1;
    }
    
    // 대상 파일을 쓰기 모드로 열기 (없으면 생성, 있으면 덮어쓰기)
    dst = fopen(argv[2], "w");
    if (!dst) {
        perror("cp: destination");
        fclose(src);  // 소스 파일 닫기
        return 1;
    }
    
    // 소스 파일에서 한 문자씩 읽어서 대상 파일에 쓰기
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }
    
    fclose(src);  // 소스 파일 닫기
    fclose(dst);  // 대상 파일 닫기
    return 0;
}