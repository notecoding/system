// seq.c - 수열 생성
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int start = 1, end = 1, step = 1;  // 시작값, 끝값, 증가값 초기화
    
    // 명령행 인자 개수에 따른 처리
    if (argc == 2) {
        // seq LAST: 1부터 LAST까지
        end = atoi(argv[1]);
    } else if (argc == 3) {
        // seq FIRST LAST: FIRST부터 LAST까지
        start = atoi(argv[1]);
        end = atoi(argv[2]);
    } else if (argc == 4) {
        // seq FIRST INCREMENT LAST: FIRST부터 INCREMENT씩 증가하여 LAST까지
        start = atoi(argv[1]);
        step = atoi(argv[2]);
        end = atoi(argv[3]);
    } else {
        fprintf(stderr, "Usage: %s [FIRST [INCREMENT]] LAST\n", argv[0]);
        return 1;
    }
    
    // 증가값이 0이면 무한루프 방지
    if (step == 0) {
        fprintf(stderr, "seq: INCREMENT must not be 0\n");
        return 1;
    }
    
    // 양수 증가값: 시작부터 끝까지 증가
    if (step > 0) {
        for (int i = start; i <= end; i += step) {
            printf("%d\n", i);
        }
    } else {
        // 음수 증가값: 시작부터 끝까지 감소
        for (int i = start; i >= end; i += step) {
            printf("%d\n", i);
        }
    }
    
    return 0;
}