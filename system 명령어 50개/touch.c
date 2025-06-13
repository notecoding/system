// touch - 빈 파일 생성 또는 시간 갱신
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    
    // 명령행 인자가 충분한지 확인 (프로그램명 + 파일명)
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // O_CREAT: 파일이 없으면 생성, O_WRONLY: 쓰기 전용으로 열기
    // 0644: 파일 권한 설정 (소유자는 읽기/쓰기, 그룹과 다른 사용자는 읽기만)
    fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("touch");
        return 1;
    }
    
    // 파일을 열었다가 바로 닫으면 파일이 생성되거나 접근 시간이 갱신됨
    close(fd);
    return 0;
}