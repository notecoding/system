// yes.c - 지정된 문자열을 무한히 출력
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *output = "y"; // 기본값은 "y"
    
    // 인자가 주어지면 해당 문자열들을 출력할 내용으로 사용
    if (argc > 1) {
        // 모든 인수를 공백으로 연결하여 하나의 문자열로 만듦
        static char buffer[1024];
        strcpy(buffer, argv[1]); // 첫 번째 인자 복사
        for (int i = 2; i < argc; i++) {
            strcat(buffer, " ");     // 공백 추가
            strcat(buffer, argv[i]); // 다음 인자 연결
        }
        output = buffer; // 연결된 문자열을 출력할 내용으로 설정
    }
    
    // 무한 루프로 지정된 문자열을 계속 출력
    while (1) {
        printf("%s\n", output);
        fflush(stdout); // 출력 버퍼를 즉시 비워서 바로 출력되도록 함
    }
    
    return 0;
}