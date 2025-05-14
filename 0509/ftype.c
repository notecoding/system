#include <sys/types.h> 
#include <sys/stat.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 /* 파일타입을검사한다. */
 intmain(intargc, char *argv[])
 { 
int i;
 structstat buf;
 for (i= 1; i< argc; i++) {
 printf("%s: ", argv[i]);
 if (lstat(argv[i], &buf) < 0) {
 perror("lstat()"); 
continue;
 }
 if (S_ISREG(buf.st_mode)) 
printf("%s \n", "일반파일");
 if (S_ISDIR(buf.st_mode)) 
printf("%s \n", "디렉터리");
 if (S_ISCHR(buf.st_mode)) 
printf("%s \n", "문자장치파일");
 if (S_ISBLK(buf.st_mode)) 
printf("%s \n", "블록장치파일");
 if (S_ISFIFO(buf.st_mode)) 
printf("%s \n", "FIFO 파일");
 if (S_ISLNK(buf.st_mode)) 
printf("%s \n", "심볼릭링크");
 if (S_ISSOCK(buf.st_mode)) 
printf("%s \n", "소켓");
 }
 exit(0);
 }
