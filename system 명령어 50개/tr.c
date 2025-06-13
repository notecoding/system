// tr - 문자 변환
#include <stdio.h>

int main(int argc, char *argv[]) {
    int ch;
    char *from, *to;
    // 변환할 문자 집합과 변환될 문자 집합 두 개의 인자가 필요
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <from> <to>\n", argv[0]);
        return 1;
    }
    from = argv[1]; // 변환할 문자들 (예: "abc")
    to = argv[2];   // 변환될 문자들 (예: "xyz")
    // 표준 입력에서 한 문자씩 읽어서 처리
    while ((ch = getchar()) != EOF) {
        int found = 0;
        // from 문자열에서 현재 문자와 일치하는 것을 찾음
        for (int i = 0; from[i] && !found; i++) {
            // 일치하는 문자를 찾았고 대응하는 to 문자가 있으면
            if (ch == from[i] && to[i]) {
                putchar(to[i]); // 대응 문자로 변환하여 출력
                found = 1;
            }
        }
        // 변환할 문자가 아니면 원본 그대로 출력
        if (!found) putchar(ch);
    }
    return 0;
}