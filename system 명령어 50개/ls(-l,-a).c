#include <stdio.h>       // 표준 입출력 함수들 (printf 등)
#include <stdlib.h>      // 일반적인 함수들 (exit, malloc 등)
#include <dirent.h>      // 디렉토리 처리 함수들 (opendir, readdir 등)
#include <sys/stat.h>    // 파일 상태 정보 구조체와 상수들 (stat 등)
#include <pwd.h>         // 사용자 ID → 사용자 이름 변환용
#include <grp.h>         // 그룹 ID → 그룹 이름 변환용
#include <time.h>        // 시간 처리 함수들 (strftime 등)
#include <string.h>      // 문자열 처리 함수들
#include <unistd.h>      // getopt 함수 사용을 위한 헤더
#include <getopt.h>      // 명령행 옵션 파싱을 위한 헤더

// 파일의 권한을 문자열 형태로 변환 (예: -rw-r--r--)
void mode_to_string(mode_t mode, char *str) {
    // 파일의 종류 판단: 디렉토리(d), 링크(l), 일반파일(-) 등
    str[0] = S_ISDIR(mode) ? 'd' : 
             S_ISLNK(mode) ? 'l' : 
             S_ISCHR(mode) ? 'c' : 
             S_ISBLK(mode) ? 'b' : 
             S_ISFIFO(mode) ? 'p' : 
             S_ISSOCK(mode) ? 's' : '-';

    // 사용자 권한 (rwx)
    str[1] = (mode & S_IRUSR) ? 'r' : '-';
    str[2] = (mode & S_IWUSR) ? 'w' : '-';
    str[3] = (mode & S_IXUSR) ? 'x' : '-';

    // 그룹 권한 (rwx)
    str[4] = (mode & S_IRGRP) ? 'r' : '-';
    str[5] = (mode & S_IWGRP) ? 'w' : '-';
    str[6] = (mode & S_IXGRP) ? 'x' : '-';

    // 기타 사용자 권한 (rwx)
    str[7] = (mode & S_IROTH) ? 'r' : '-';
    str[8] = (mode & S_IWOTH) ? 'w' : '-';
    str[9] = (mode & S_IXOTH) ? 'x' : '-';

    str[10] = '\0';  // 문자열 끝 표시
}

// -l 옵션일 때 상세 정보 출력하는 함수
void print_long_format(const char *path, const char *name) {
    struct stat file_stat;         // 파일 상태 정보 저장 구조체
    char full_path[1024];          // 파일 전체 경로 저장
    char mode_str[11];             // 권한 문자열 (예: -rw-r--r--)
    char time_str[13];             // 시간 문자열 (예: Jun 12 17:00)
    struct passwd *pw;             // 사용자 정보
    struct group *gr;              // 그룹 정보

    // 경로 + 파일 이름 → 전체 경로 구성
    snprintf(full_path, sizeof(full_path), "%s/%s", path, name);

    // 파일 상태 정보 얻기
    if (stat(full_path, &file_stat) == -1) {
        perror("stat");  // 오류 메시지 출력
        return;
    }

    // 파일 모드를 문자열로 변환 (예: -rw-r--r--)
    mode_to_string(file_stat.st_mode, mode_str);

    // UID/GID → 사용자명/그룹명
    pw = getpwuid(file_stat.st_uid);
    gr = getgrgid(file_stat.st_gid);

    // 수정 시간 → 사람이 보기 쉬운 문자열로 변환
    struct tm *timeinfo = localtime(&file_stat.st_mtime);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);

    // 출력 형식: 권한 링크수 사용자 그룹 크기 시간 이름
    printf("%s %3ld %-8s %-8s %8ld %s %s\n",
           mode_str,
           file_stat.st_nlink,                     // 하드 링크 수
           pw ? pw->pw_name : "unknown",          // 사용자명 (없으면 unknown)
           gr ? gr->gr_name : "unknown",          // 그룹명
           file_stat.st_size,                     // 파일 크기 (bytes)
           time_str,                              // 수정 시간
           name);                                 // 파일 이름
}

// -l 옵션이 없을 때 단순히 파일 이름만 출력
void print_simple_format(const char *name) {
    printf("%s  ", name);  // 파일명 뒤에 공백 붙여 출력
}

int main(int argc, char *argv[]) {
    DIR *dir;                      // 디렉토리 포인터
    struct dirent *entry;          // 디렉토리 항목 구조체
    char *directory = ".";         // 기본 디렉토리는 현재 디렉토리
    int long_format = 0;           // -l 옵션 여부 (0: 꺼짐, 1: 켜짐)
    int show_hidden = 0;           // -a 옵션 여부 (숨김파일 출력)
    int opt;                       // getopt 결과 저장 변수

    // getopt로 옵션 파싱 (-l, -a만 처리)
    while ((opt = getopt(argc, argv, "la")) != -1) {
        switch (opt) {
            case 'l':
                long_format = 1;  // 상세 출력 모드 켜기
                break;
            case 'a':
                show_hidden = 1;  // 숨김파일 포함 모드 켜기
                break;
            case '?':  // 알 수 없는 옵션 처리
                fprintf(stderr, "알 수 없는 옵션: -%c\n", optopt);
                fprintf(stderr, "사용법: %s [-l] [-a] [디렉토리]\n", argv[0]);
                return 1;
            default:
                fprintf(stderr, "옵션 처리 오류\n");
                return 1;
        }
    }

    // 옵션 다음에 오는 인수가 디렉토리 경로라면 설정
    if (optind < argc) {
        directory = argv[optind];
    }

    // 디렉토리 열기
    dir = opendir(directory);
    if (!dir) {
        perror("ls");  // 디렉토리 열기 실패
        return 1;
    }

    // -l 옵션이면 total 블록 수 먼저 출력
    if (long_format) {
        long total_blocks = 0;
        rewinddir(dir);  // 디렉토리 포인터 위치 초기화

        // 디렉토리 내부 파일 순회
        while ((entry = readdir(dir))) {
            // 숨김 파일은 옵션 없으면 건너뜀
            if (!show_hidden && entry->d_name[0] == '.')
                continue;

            struct stat file_stat;
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", directory, entry->d_name);

            // 파일 상태 정보 가져오기
            if (stat(full_path, &file_stat) == 0) {
                total_blocks += file_stat.st_blocks;  // 블록 수 누적
            }
        }

        // 512바이트 단위를 1KB 단위로 나누어 출력
        printf("total %ld\n", total_blocks / 2);
        rewinddir(dir);  // 다시 출력 위해 포인터 초기화
    }

    // 실제 파일 목록 출력
    while ((entry = readdir(dir))) {
        if (!show_hidden && entry->d_name[0] == '.')
            continue;

        if (long_format) {
            print_long_format(directory, entry->d_name);  // 상세 출력
        } else {
            print_simple_format(entry->d_name);           // 간단 출력
        }
    }

    if (!long_format) {
        printf("\n");  // 줄 바꿈
    }

    closedir(dir);  // 디렉토리 닫기
    return 0;       // 정상 종료
}
