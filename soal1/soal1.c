#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main() {
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

    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1) {
        struct dirent *de;
        char nama_awal[100], name[100];
    	char opo[100] = "/home/affan/modul2/gambar/";
    	char opo1[100];
    	char apa1[100];

    	DIR *dr = opendir("/home/affan/modul2/gambar"); 

        if (dr != NULL)	{
            while ((de = readdir(dr)) != NULL) {
                 char *end = strrchr(de->d_name, '.');
                 if(strcmp(end, ".png") == 0) {	
                     strcpy(opo1, opo);
                     strcpy(apa1, opo);
                     
                     strcpy(nama_awal, de->d_name);
                     de->d_name[strlen(de->d_name)-4]='\0';
                     strcpy(name, de->d_name);
						
                    strcat(name,"_grey.png");
                    strcat(opo1, name);
                    strcat(apa1, nama_awal);

                    rename(apa1, opo1);
                }
            }
        }
        else
        { 
            printf("Could not open current directory"); 
        } 

        closedir(dr);
        sleep(30);
    }
  
    exit(EXIT_SUCCESS);
}