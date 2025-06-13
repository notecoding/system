#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int shred_file(const char *filename, int passes) {
    // 파일을 읽기/쓰기 바이너리 모드로 열기
    FILE *file = fopen(filename, "r+b");
    if (!file) {
        perror("shred");
        return -1;
    }
    
    // fstat으로 파일 크기 정보 획득
    struct stat st;
    if (fstat(fileno(file), &st) == -1) {
        perror("shred");
        fclose(file);
        return -1;
    }
    size_t file_size = st.st_size;  // 파일 크기 저장
    // 파일 크기만큼 메모리 할당
    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "shred: memory allocation failed\n");
        fclose(file);
        return -1;
    }
    
    srand(time(NULL));  // 난수 생성기 초기화
    
    // 지정된 횟수만큼 덮어쓰기 수행
    for (int pass = 0; pass < passes; pass++) {
        printf("shred: %s: pass %d/%d...\n", filename, pass + 1, passes);
        
        // 버퍼를 랜덤 데이터로 채움
        for (size_t i = 0; i < file_size; i++) {
            buffer[i] = rand() % 256;  // 0-255 범위의 랜덤 바이트
        }
        
        // 파일 시작 위치로 이동하여 랜덤 데이터 쓰기
        fseek(file, 0, SEEK_SET);
        fwrite(buffer, 1, file_size, file);
        fflush(file);        // 버퍼를 디스크에 강제 쓰기
        fsync(fileno(file)); // 시스템 버퍼도 디스크에 동기화
    }
    
    free(buffer);
    fclose(file);
    
    // 덮어쓰기 완료 후 파일 삭제
    if (unlink(filename) == -1) {
        perror("shred");
        return -1;
    }
    
    return 0;
}

int main(int argc, char *argv[]) {
    int passes = 3;  // 기본 덮어쓰기 횟수
    int opt;
    
    // getopt로 -n 옵션 처리
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                passes = atoi(optarg);  // 덮어쓰기 횟수 설정
                if (passes <= 0) {
                    fprintf(stderr, "shred: invalid number of passes\n");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                fprintf(stderr, "Usage: %s [-n passes] file...\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    // 파일명이 주어지지 않은 경우
    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n passes] file...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // 주어진 모든 파일에 대해 shred 수행
    for (int i = optind; i < argc; i++) {
        if (shred_file(argv[i], passes) == -1) {
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}