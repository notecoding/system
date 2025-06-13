#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

mode_t parse_mode(const char *mode_str) {
    mode_t mode = 0;
    
    // 3자리 8진수 모드 파싱 (예: 755, 644)
    if (strlen(mode_str) == 3 && 
        mode_str[0] >= '0' && mode_str[0] <= '7' &&  // 첫 번째 자리 검증
        mode_str[1] >= '0' && mode_str[1] <= '7' &&  // 두 번째 자리 검증
        mode_str[2] >= '0' && mode_str[2] <= '7') {  // 세 번째 자리 검증
        
        // 8진수를 비트 시프트로 변환
        // 소유자 권한 (6비트 시프트) | 그룹 권한 (3비트 시프트) | 기타 권한
        mode = (mode_str[0] - '0') << 6 |
               (mode_str[1] - '0') << 3 |
               (mode_str[2] - '0');
    }
    
    return mode;
}

int main(int argc, char *argv[]) {
    // 정확히 3개의 인수 필요 (프로그램명, 모드, 파일명)
    if (argc != 3) {
        fprintf(stderr, "Usage: %s mode file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // 모드 문자열을 파싱하여 mode_t 값으로 변환
    mode_t mode = parse_mode(argv[1]);
    if (mode == 0) {
        fprintf(stderr, "Invalid mode: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // chmod 시스템 콜로 파일 권한 변경
    if (chmod(argv[2], mode) == -1) {
        perror("chmod");  // 실패 시 에러 메시지 출력
        exit(EXIT_FAILURE);
    }
    
    return 0;
}