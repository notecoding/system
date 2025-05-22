 1 #include <stdio.h>
 2 #include <fcntl.h>
 3 #include <unistd.h>
 4
 5 /* 표준출력을 파일에 재지정하는 프로그램*/
 6 int main(int argc, char* argv[])
 7 {
 8     
int fd, status;
 9     
10     
fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0600);
 dup2(fd, 1); /* 파일을 표준출력에 복제 */
 11    close(fd);
 12    printf("Hello stdout !\n");
 13    fprintf(stderr,"Hello stderr !\n");
 14 }