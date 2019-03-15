#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

int main(){
    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
      exit(EXIT_FAILURE);
    }

    if (pid > 0) {
      exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0) {
      exit(EXIT_FAILURE);
    }

    if ((chdir("/home/affan/modul2/no4")) < 0) {
      exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int count=1;
    char dir[100] = "/home/affan/modul2/makanan/makanan_sehat";
    char newfile[100];

    while(1){

        time_t now;
        time(&now);
        struct stat st = {0};
        double diff = difftime(now,st.st_atime);
        if(diff <= 30){
            FILE *remind;
            snprintf(newfile, 13,"%d.txt",count);

            strcat(dir,newfile);
            remind = fopen(dir,"w+");
            fclose(remind);
            count++;
        }

        sleep(5);
    }
    exit(EXIT_SUCCESS);
}
