#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int symbolic = 0;  // 심볼릭 링크 플래그
    int opt;
    
    // 명령행 옵션 파싱 (-s 옵션)
    while ((opt = getopt(argc, argv, "s")) != -1) {
        switch (opt) {
            case 's':
                symbolic = 1;  // 심볼릭 링크 생성 모드
                break;
            default:
                fprintf(stderr, "Usage: %s [-s] target linkname\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    // 옵션을 제외하고 정확히 2개의 인수 필요
    if (argc - optind != 2) {
        fprintf(stderr, "Usage: %s [-s] target linkname\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *target = argv[optind];      // 링크할 대상 파일
    char *linkname = argv[optind + 1]; // 생성할 링크 이름
    
    int result;
    if (symbolic) {
        // 심볼릭 링크 생성
        result = symlink(target, linkname);
    } else {
        // 하드 링크 생성
        result = link(target, linkname);
    }
    
    // 링크 생성 실패 시 에러 처리
    if (result == -1) {
        perror("ln");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}