// cal.c - 달력 출력
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_leap_year(int year) {
    // 윤년 판별: 4로 나누어떨어지고 100으로 나누어떨어지지 않거나, 400으로 나누어떨어짐
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    // 각 달의 일수 (1월=31일, 2월=28일, ...)
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // 2월이고 윤년이면 29일
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days[month - 1];  // 배열 인덱스는 0부터 시작하므로 -1
}

int day_of_week(int day, int month, int year) {
    // Zeller's congruence 공식으로 요일 계산
    if (month < 3) {
        month += 12;  // 1월과 2월을 전년도의 13월, 14월로 처리
        year--;
    }
    int k = year % 100;       // 년도의 뒤 두 자리
    int j = year / 100;       // 년도의 앞 두 자리
    int h = (day + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;
    return (h + 5) % 7;  // 0=Sunday, 1=Monday, ...
}

void print_calendar(int month, int year) {
    char *months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};
    
    // 달력 제목 출력
    printf("     %s %d\n", months[month - 1], year);
    printf("Su Mo Tu We Th Fr Sa\n");
    
    int first_day = day_of_week(1, month, year);  // 1일의 요일
    int days = days_in_month(month, year);        // 해당 월의 총 일수
    
    // 첫 주의 공백 출력 (1일이 일요일이면 공백 없음)
    for (int i = 0; i < first_day; i++) {
        printf("   ");
    }
    
    // 날짜 출력
    for (int day = 1; day <= days; day++) {
        printf("%2d ", day);  // 2자리로 정렬하여 출력
        // 토요일이면 줄바꿈
        if ((day + first_day) % 7 == 0) {
            printf("\n");
        }
    }
    
    // 마지막 줄이 완성되지 않았으면 줄바꿈
    if ((days + first_day) % 7 != 0) {
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    // 현재 날짜 정보 가져오기
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int month = tm_info->tm_mon + 1;        // tm_mon은 0부터 시작하므로 +1
    int year = tm_info->tm_year + 1900;     // tm_year는 1900년부터의 년수
    
    // 명령행 인수에 따라 년도 또는 월/년도 설정
    if (argc == 2) {
        year = atoi(argv[1]);               // 년도만 지정
    } else if (argc == 3) {
        month = atoi(argv[1]);              // 월과 년도 지정
        year = atoi(argv[2]);
    }
    
    // 월 범위 체크
    if (month < 1 || month > 12) {
        fprintf(stderr, "cal: invalid month\n");
        return 1;
    }
    
    print_calendar(month, year);
    return 0;
}