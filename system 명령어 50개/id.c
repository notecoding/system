// id - 사용자 ID 정보 출력
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main() {
    uid_t uid = getuid();                   // 사용자 ID 가져오기
    gid_t gid = getgid();                   // 그룹 ID 가져오기
    struct passwd *pw = getpwuid(uid);      // 사용자 이름 정보 가져오기
    struct group *gr = getgrgid(gid);       // 그룹 이름 정보 가져오기
    
    // 사용자 ID 출력
    printf("uid=%d", uid);
    if (pw) printf("(%s)", pw->pw_name);    // 사용자 이름 출력
    
    // 그룹 ID 출력
    printf(" gid=%d", gid);
    if (gr) printf("(%s)", gr->gr_name);    // 그룹 이름 출력
    
    printf("\n");
    return 0;
}