#include <stdio.h>
#include <stdlib.h>

int main() {
    // ANSI escape sequence로 화면 지우기
    // \033[2J: 전체 화면 지우기, \033[H: 커서를 홈 위치(좌상단)로 이동
    printf("\033[2J\033[H");
    fflush(stdout);  // 출력 버퍼 강제로 비우기 (즉시 화면에 반영)
    return 0;
}