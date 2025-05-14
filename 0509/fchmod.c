 #include <sys/types.h>
 #include <sys/stat.h>
 #include <stdio.h>
 #include <stdlib.h>
 /* 파일사용권한을변경한다. */
 main(int argc, char *argv[])
 {
 long strtol( );
 int newmode;
 newmode = (int) strtol(argv[1], (char **) NULL, 8);
 if (chmod(argv[2], newmode) == -1) {
 perror(argv[2]);
 exit(1);
 }
 exit(0);
 }
