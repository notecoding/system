// free.c - 메모리 사용량 표시
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp;
    char line[256];
    long mem_total = 0, mem_free = 0, mem_available = 0;
    long swap_total = 0, swap_free = 0;
    
    // /proc/meminfo 파일 열기 (리눅스 메모리 정보)
    fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("fopen /proc/meminfo");
        return 1;
    }
    
    // 파일을 한 줄씩 읽어서 필요한 정보 추출
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line, "MemTotal: %ld kB", &mem_total);
        } else if (strncmp(line, "MemFree:", 8) == 0) {
            sscanf(line, "MemFree: %ld kB", &mem_free);
        } else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line, "MemAvailable: %ld kB", &mem_available);
        } else if (strncmp(line, "SwapTotal:", 10) == 0) {
            sscanf(line, "SwapTotal: %ld kB", &swap_total);
        } else if (strncmp(line, "SwapFree:", 9) == 0) {
            sscanf(line, "SwapFree: %ld kB", &swap_free);
        }
    }
    
    fclose(fp);
    
    // free 명령어와 유사한 형태로 출력
    printf("              total        used        free      shared  buff/cache   available\n");
    printf("Mem:    %10ld %10ld %10ld %10d %10d %10ld\n",
           mem_total, mem_total - mem_free, mem_free, 0, 0, mem_available);
    printf("Swap:   %10ld %10ld %10ld\n",
           swap_total, swap_total - swap_free, swap_free);
    
    return 0;
}