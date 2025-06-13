// tail - 파일의 마지막 몇 줄 출력
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char *lines[10];     // 마지막 10줄을 저장할 배열
    char buffer[1024];   // 한 줄을 읽기 위한 버퍼
    int count = 0, i;
    
    // 명령행 인자 개수 확인
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    file = fopen(argv[1], "r");
    if (!file) {
        perror("tail");
        return 1;
    }
    
    // 배열 초기화 (모든 포인터를 NULL로 설정)
    for (i = 0; i < 10; i++) lines[i] = NULL;
    
    // 파일에서 한 줄씩 읽어서 순환 배열에 저장
    while (fgets(buffer, sizeof(buffer), file)) {
        // 기존 메모리가 있으면 해제
        if (lines[count % 10]) free(lines[count % 10]);
        // 새로운 줄을 복사하여 저장 (순환 배열 방식)
        lines[count % 10] = strdup(buffer);
        count++;  // 총 줄 수 증가
    }
    
    // 출력 시작 위치 계산
    int start = (count < 10) ? 0 : count % 10;  // 10줄 미만이면 0부터, 이상이면 순환 위치부터
    int total = (count < 10) ? count : 10;      // 출력할 총 줄 수
    
    // 마지막 최대 10줄을 순서대로 출력
    for (i = 0; i < total; i++) {
        printf("%s", lines[(start + i) % 10]);  // 순환 배열에서 순서대로 출력
    }
    
    // 할당된 메모리 해제
    for (i = 0; i < 10; i++) {
        if (lines[i]) free(lines[i]);
    }
    fclose(file);
    return 0;
}