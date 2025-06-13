// find - 파일 검색 (간단한 버전)
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void search_dir(char *path, char *name) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    struct stat st;
    char full_path[1024];
    
    if (!dir) return;  // 디렉토리 열기 실패 시 종료
    
    // 디렉토리 내 모든 항목 검사
    while ((entry = readdir(dir))) {
        // "."과 ".." 디렉토리는 제외
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
            
        // 전체 경로 생성
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
        // 파일명에 검색어가 포함되어 있는지 확인
        if (strstr(entry->d_name, name)) {
            printf("%s\n", full_path);
        }
        
        // 디렉토리인 경우 재귀적으로 검색
        if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode)) {
            search_dir(full_path, name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    // 경로와 검색할 이름이 필요
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <path> <name>\n", argv[0]);
        return 1;
    }
    
    // 지정된 경로에서 검색 시작
    search_dir(argv[1], argv[2]);
    return 0;
}