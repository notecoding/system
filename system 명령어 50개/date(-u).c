// date - 현재 날짜와 시간 출력 (-u 옵션 지원)
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    struct tm *tm;

    // -u 옵션이 있으면 UTC 시간, 없으면 로컬 시간
    if (argc > 1 && strcmp(argv[1], "-u") == 0) {
        tm = gmtime(&t);  // UTC 시간
    } else {
        tm = localtime(&t);  // 로컬 시간
    }

    printf("%s", asctime(tm));
    return 0;
}