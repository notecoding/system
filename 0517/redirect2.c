 1 #include <sys/types.h>
 2 #include <sys/wait.h>
 3 #include <stdio.h>
 4 #include <fcntl.h>
 5 #include <unistd.h>
 6
 7 /* 자식프로세스의표준출력을파
일에재지정한다. */
 8 intmain(intargc, char* argv[])
 9 {
 10    intchild, pid, fd, status;
 11
 12    pid= fork( );
 13  if (pid== 0) {
 14      fd= open(argv[1],O_CREAT|
 O_TRUNC| O_WRONLY, 0600);
 15      dup2(fd, 1);   // 파일을표준출력에복제
16      close(fd);
 17      execvp(argv[2], &argv[2]);
 18      fprintf(stderr, "%s:실행불가\n",argv[1]);
 19    } else {
 20       child = wait(&status);
 21       printf("[%d] 자식프로세스%d 종료\n", 
getpid(), child);
 22    }
 23 }