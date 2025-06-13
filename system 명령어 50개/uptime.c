// uptime.c - 시스템 가동 시간 표시
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;
    time_t current_time;
    struct tm *time_info;
    
    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return 1;
    }
    
    current_time = time(NULL);
    time_info = localtime(&current_time);
    
    int uptime_days = info.uptime / 86400;
    int uptime_hours = (info.uptime % 86400) / 3600;
    int uptime_minutes = (info.uptime % 3600) / 60;
    
    printf(" %02d:%02d:%02d up ",
           time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    
    if (uptime_days > 0) {
        printf("%d day%s, ", uptime_days, uptime_days > 1 ? "s" : "");
    }
    
    printf("%d:%02d, ", uptime_hours, uptime_minutes);
    printf("load average: %.2f, %.2f, %.2f\n",
           (float)info.loads[0] / 65536.0,
           (float)info.loads[1] / 65536.0,
           (float)info.loads[2] / 65536.0);
    
    return 0;
}