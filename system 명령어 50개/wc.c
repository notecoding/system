// wc - 단어, 줄, 문자 수 세기
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    int lines = 0, words = 0, chars = 0; // 줄 수, 단어 수, 문자 수 카운터
    char ch, prev = ' '; // 현재 문자와 이전 문자 (단어 구분을 위해)
    
    // 파일명이 인자로 주어져야 함
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    file = fopen(argv[1], "r");
    if (!file) {
        perror("wc");
        return 1;
    }
    
    // 파일에서 한 문자씩 읽어서 처리
    while ((ch = fgetc(file)) != EOF) {
        chars++; // 문자 수 증가
        if (ch == '\n') lines++; // 개행 문자면 줄 수 증가
        
        // 현재 문자가 공백/탭/개행이고 이전 문자가 그렇지 않으면 단어 끝
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (prev != ' ' && prev != '\n' && prev != '\t') words++;
        }
        prev = ch; // 이전 문자로 저장
    }
    
    // 파일이 공백으로 끝나지 않는 경우 마지막 단어 처리
    if (prev != ' ' && prev != '\n' && prev != '\t' && chars > 0) words++;
    
    // "줄수 단어수 문자수 파일명" 형식으로 출력
    printf("%d %d %d %s\n", lines, words, chars, argv[1]);
    fclose(file);
    return 0;
}