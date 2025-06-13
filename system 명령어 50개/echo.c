// echo - 텍스트 출력
#include <stdio.h>

int main(int argc, char *argv[]) {
    // 첫 번째 인수부터 마지막까지 출력
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        // 마지막 인수가 아니면 공백 추가
        if (i < argc - 1) printf(" ");
    }
    printf("\n");  // 마지막에 개행 추가
    return 0;
}