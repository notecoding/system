// sort - 텍스트 정렬
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// qsort에서 사용할 문자열 비교 함수
int compare(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);  // 두 문자열을 사전식으로 비교
}

int main(int argc, char *argv[]) {
    FILE *file;
    char **lines = NULL;  // 문자열 포인터 배열 (각 줄을 저장)
    char buffer[1024];    // 한 줄을 읽기 위한 임시 버퍼
    int count = 0, capacity = 10;  // 현재 줄 수, 배열 용량
    
    // 명령행 인자 개수 확인
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    file = fopen(argv[1], "r");
    if (!file) {
        perror("sort");
        return 1;
    }
    
    // 문자열 포인터 배열 초기 할당
    lines = malloc(capacity * sizeof(char*));
    
    // 파일에서 한 줄씩 읽어서 배열에 저장
    while (fgets(buffer, sizeof(buffer), file)) {
        // 배열이 가득 찬 경우 크기를 2배로 확장
        if (count >= capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char*));
        }
        lines[count] = strdup(buffer);  // 문자열 복사하여 저장
        count++;
    }
    
    // qsort로 문자열 배열 정렬
    qsort(lines, count, sizeof(char*), compare);
    
    // 정렬된 문자열들 출력 후 메모리 해제
    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);  // 각 문자열 메모리 해제
    }
    
    free(lines);  // 포인터 배열 메모리 해제
    fclose(file);
    return 0;
}