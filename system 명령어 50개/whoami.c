// whoami - 현재 사용자명 출력
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main() {
    // getuid(): 현재 프로세스의 사용자 ID를 얻음
    // getpwuid(): 사용자 ID로 passwd 구조체(사용자 정보)를 얻음
    struct passwd *pw = getpwuid(getuid());
    if (pw) {
        // pw_name: passwd 구조체의 사용자명 필드
        printf("%s\n", pw->pw_name);
    } else {
        perror("whoami");
        return 1;
    }
    return 0;
}