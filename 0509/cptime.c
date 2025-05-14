#include <sys/types.h> #include <sys/stat.h> 
#include <sys/time.h> #include <utime.h> 
#include <stdio.h>      #include <stdlib.h>
 intmain(intargc, char *argv[]) 
{
 structstat buf;        // 파일상태저장을위한변수
structutimbuf time;
 if (argc< 3) {
 fprintf(stderr, "사용법: cptimefile1 file2\n");
 exit(1);
 }
 if (stat(argv[1], &buf) <0) { // 상태가져오기
perror("stat()");
 exit(-1);
 }
 time.actime= buf.st_atime;
 time.modtime= buf.st_mtime;
 if (utime(argv[2], &time))   // 접근, 수정시간복사
perror("utime");
 else exit(0);
 }
