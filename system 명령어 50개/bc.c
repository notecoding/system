// bc.c - 간단한 계산기 (기본 사칙연산만)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

double evaluate_expression(const char *expr) {
    // 매우 간단한 구현 - 단일 연산만 지원
    char op;
    double num1, num2;
    
    // sscanf로 "숫자 연산자 숫자" 형태의 문자열을 파싱
    if (sscanf(expr, "%lf %c %lf", &num1, &op, &num2) == 3) {
        switch (op) {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': 
                // 0으로 나누기 방지
                if (num2 == 0) {
                    fprintf(stderr, "Division by zero\n");
                    return 0;
                }
                return num1 / num2;
            default:
                fprintf(stderr, "Unknown operator: %c\n", op);
                return 0;
        }
    } else {
        // 단일 숫자인 경우 (연산자가 없음)
        return atof(expr);
    }
}

int main(int argc, char *argv[]) {
    char line[256];
    
    // 명령행 인수가 있으면 각각을 계산
    if (argc > 1) {
        // 명령행 인수로 표현식 받기
        for (int i = 1; i < argc; i++) {
            double result = evaluate_expression(argv[i]);
            printf("%.6g\n", result);  // %.6g: 소수점 6자리까지, 불필요한 0 제거
        }
    } else {
        // 대화형 모드
        printf("Simple calculator (type 'quit' to exit)\n");
        while (1) {
            printf("bc> ");
            // 사용자 입력 받기
            if (!fgets(line, sizeof(line), stdin)) {
                break;
            }
            
            // 개행 문자 제거 (fgets는 \n도 포함해서 읽음)
            line[strcspn(line, "\n")] = 0;
            
            // "quit" 입력 시 종료
            if (strcmp(line, "quit") == 0) {
                break;
            }
            
            double result = evaluate_expression(line);
            printf("%.6g\n", result);
        }
    }
    
    return 0;
}