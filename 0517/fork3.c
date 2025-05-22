#include <stdlib.h>
 #include <stdio.h>
 /* 부모 프로세스가 두개의자식프로세스를생성한다. */
 int main() 
{
 int pid1, pid2;
 pid1 = fork();
 if (pid1 == 0) {
 printf("[Child 1] : Hello, world ! pid=%d\n", getpid());
 exit(0);
 }
 pid2 = fork();
 if (pid2 == 0) {
 printf("[Child 2] : Hello, world ! pid=%d\n", getpid());
 exit(0);
 }
 printf("[PARENT] : Hello, world ! pid=%d\n",getpid());
 } 
