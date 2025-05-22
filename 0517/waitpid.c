 1  #include <sys/types.h>
 …
 7   /* 부모프로세스가자식프로세스를생성하고끝나기를기다린다. */
 8 intmain() 
9 {
 10 intpid1, pid2, child, status;
 11
 12      printf("[%d] 부모프로세스시작\n", getpid( ));
 13 pid1 = fork();
 14 if (pid1 == 0) {
 15 printf("[%d] 자식프로세스[1] 시작\n", getpid( ));
 16 sleep(1);
 17 printf("[%d] 자식프로세스[1] 종료\n", getpid( ));
 18 exit(1);
 19 }
  pid2 = fork();
 22 if (pid2 == 0) {
 23 printf("[%d] 자식프로세스#2 시작\n", getpid( ));
 24 sleep(2);
 25 printf("[%d] 자식프로세스#2 종료\n", getpid( ));
 26 exit(2);
 27 }
 28 // 자식프로세스#1의종료를기다린다.
 29 child = waitpid(pid1, &status, 0); 
30 printf("[%d] 자식프로세스#1 %d 종료\n", getpid( ), child);
 31 printf("\t종료코드%d\n", status>>8);
 32 }