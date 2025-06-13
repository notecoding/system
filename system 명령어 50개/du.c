// du.c - 디스크 사용량 표시
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

long get_dir_size(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    long total_size = 0;
    char full_path[1024];
    
    // 디렉토리 열기
    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return 0;
    }
    
    // 디렉토리 내 모든 항목 순회
    while ((entry = readdir(dir)) != NULL) {
        // "."과 ".." 디렉토리는 제외
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        // 전체 경로 생성
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        // 파일/디렉토리 정보 가져오기
        if (stat(full_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                // 디렉토리면 재귀적으로 크기 계산
                total_size += get_dir_size(full_path);
            } else {
                // 파일이면 크기 추가
                total_size += st.st_size;
            }
        }
    }
    
    closedir(dir);
    return total_size;
}

int main(int argc, char *argv[]) {
    // 인수가 없으면 현재 디렉토리 사용
    const char *path = (argc > 1) ? argv[1] : ".";
    long size = get_dir_size(path);
    
    // KB 단위로 변환하여 출력
    printf("%ld\t%s\n", size / 1024, path);
    return 0;
}