 #include <stdio.h>
 #include <unistd.h>
 #include <fcntl.h>
 #define BUFSIZE 512
 /* 파일크기를계산한다*/
 intmain(intargc, char *argv[]) 
{
 char buffer[BUFSIZE];
 int fd;
 ssize_tnread;
 long total = 0;
 if ((fd= open(argv[1], O_RDONLY)) == -1) 
perror(argv[1]);
/* 파일의끝에도달할때까지반복해서읽으면서파일크기계산*/
 while( (nread= read(fd, buffer,    BUFSIZE)) > 0)
 total += nread;
 close(fd);
 printf ("%s 파일크기: %ld바이트\n", argv[1], total);
 exit(0);
 }
