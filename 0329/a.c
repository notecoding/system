#include <stdio.h>

int main(){
    char a;
    while(1){
        printf("문자 입력:");

        scanf("%c",&a);
        getchar();

        if(a=='0'){
            break;
        }

        if(a>=65 && a<=90){
            printf("%c의 소문자는 %c입니다.\n",a,a+32);
        }
        else if(a>=97 && a<=122){
            printf("%c의 대문자는 %c입니다.\n",a,a-32);
        }
    }
}