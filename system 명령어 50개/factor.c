// factor.c - 소인수분해
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void factorize(long long n) {
    printf("%lld:", n);
    
    // 2로 나누기 (짝수 처리)
    while (n % 2 == 0) {
        printf(" 2");
        n /= 2;
    }
    
    // 3부터 sqrt(n)까지 홀수로 나누기
    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            printf(" %lld", i);
            n /= i;
        }
    }
    
    // n이 2보다 큰 소수인 경우 (남은 수가 소수)
    if (n > 2) {
        printf(" %lld", n);
    }
    
    printf("\n");
}

int main(int argc, char *argv[]) {
    // 최소 하나의 숫자가 필요
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number> [number2] ...\n", argv[0]);
        return 1;
    }
    
    // 모든 인수에 대해 소인수분해 실행
    for (int i = 1; i < argc; i++) {
        long long n = atoll(argv[i]);  // 문자열을 long long으로 변환
        if (n <= 0) {
            fprintf(stderr, "factor: '%s' is not a valid positive integer\n", argv[i]);
            continue;
        }
        factorize(n);
    }
    
    return 0;
}