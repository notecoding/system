 1 #include <sys/types.h>
 2 #include <sys/stat.h>
 3 #include <dirent.h>
 4 #include <stdio.h>
 5 #include <stdlib.h>
 6
 7 /* 디렉터리내의파일이름들을리스트한다. */
 8 intmain(intargc, char **argv)
 9 {
 10   DIR *dp;
 11   char *dir;
 12   structdirent*d;
 13   structstat st;
 14   char path[BUFSIZ+1];
 15
