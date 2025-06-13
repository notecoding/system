// df.c - 파일시스템 디스크 공간 사용량 표시
#include <stdio.h>
#include <sys/statvfs.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    struct statvfs stat;
    // 인수가 없으면 루트 디렉토리("/")를 기본값으로 사용
    const char *path = (argc > 1) ? argv[1] : "/";
    
    // statvfs 시스템 콜로 파일시스템 정보 가져오기
    if (statvfs(path, &stat) != 0) {
        perror("statvfs");
        return 1;
    }
    
    // 파일시스템 통계 계산
    unsigned long block_size = stat.f_frsize;      // 블록 크기
    unsigned long total_blocks = stat.f_blocks;    // 전체 블록 수
    unsigned long free_blocks = stat.f_bavail;     // 일반 사용자가 사용 가능한 블록 수
    unsigned long used_blocks = total_blocks - stat.f_bfree;  // 사용 중인 블록 수
    
    // KB 단위로 변환
    unsigned long total_size = (total_blocks * block_size) / 1024;
    unsigned long used_size = (used_blocks * block_size) / 1024;
    unsigned long free_size = (free_blocks * block_size) / 1024;
    
    // df 명령어와 유사한 형태로 출력
    printf("Filesystem\t1K-blocks\tUsed\tAvailable\tUse%%\tMounted on\n");
    printf("%s\t\t%lu\t\t%lu\t%lu\t\t%lu%%\t%s\n", 
           "filesystem", total_size, used_size, free_size,
           (used_size * 100) / total_size, path);  // 사용률 계산
    
    return 0;
}