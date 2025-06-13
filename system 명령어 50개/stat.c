#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

// 파일 권한을 문자열로 출력하는 함수
void print_permissions(mode_t mode) {
    printf("(");
    printf((S_ISDIR(mode)) ? "d" : "-");      // 디렉토리 여부
    printf((mode & S_IRUSR) ? "r" : "-");     // 소유자 읽기 권한
    printf((mode & S_IWUSR) ? "w" : "-");     // 소유자 쓰기 권한
    printf((mode & S_IXUSR) ? "x" : "-");     // 소유자 실행 권한
    printf((mode & S_IRGRP) ? "r" : "-");     // 그룹 읽기 권한
    printf((mode & S_IWGRP) ? "w" : "-");     // 그룹 쓰기 권한
    printf((mode & S_IXGRP) ? "x" : "-");     // 그룹 실행 권한
    printf((mode & S_IROTH) ? "r" : "-");     // 기타 읽기 권한
    printf((mode & S_IWOTH) ? "w" : "-");     // 기타 쓰기 권한
    printf((mode & S_IXOTH) ? "x" : "-");     // 기타 실행 권한
    printf(")");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct stat st;
    // stat 시스템 콜로 파일 상태 정보 획득
    if (stat(argv[1], &st) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    
    // 파일 기본 정보 출력
    printf("  File: %s\n", argv[1]);
    printf("  Size: %ld\n", st.st_size);      // 파일 크기 (바이트)
    printf("Blocks: %ld\n", st.st_blocks);    // 할당된 블록 수
    printf("  Mode: %o ", st.st_mode & 0777); // 8진수 권한 표시
    print_permissions(st.st_mode);             // 권한을 문자로 표시
    printf("\n");
    
    // 소유자와 그룹 정보 출력
    struct passwd *pw = getpwuid(st.st_uid);  // UID로 사용자 정보 획득
    struct group *gr = getgrgid(st.st_gid);   // GID로 그룹 정보 획득
    printf("   Uid: %d/%s\n", st.st_uid, pw ? pw->pw_name : "unknown");
    printf("   Gid: %d/%s\n", st.st_gid, gr ? gr->gr_name : "unknown");
    
    // 파일 시간 정보 출력
    printf("Access: %s", ctime(&st.st_atime)); // 마지막 접근 시간
    printf("Modify: %s", ctime(&st.st_mtime)); // 마지막 수정 시간
    printf("Change: %s", ctime(&st.st_ctime)); // 마지막 상태 변경 시간
    
    return 0;
}