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
16   if (argc== 1)
 17      dir= "."; // 현재디렉터리를대상으로
18   else dir= argv[1];
 19
 20   if ((dp= opendir(dir)) == NULL) // 디렉터리열기
21      perror(dir);
 22
 23   while ((d = readdir(dp)) != NULL) // 각디렉터리엔트리에대해
24      printf("%s \n", d->d_name); // 파일이름프린트
25
 26   closedir(dp);
 27   exit(0);
 28 }
