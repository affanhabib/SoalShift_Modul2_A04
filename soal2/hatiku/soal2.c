#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <grp.h>
#include <dirent.h>
#include <unistd.h>
#include  <pwd.h>

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

  if ((chdir("/home/affan/modul2/hatiku")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO); 

 char file[100];
 DIR *dir;
 struct dirent *rent;
 while(1) {
 if ((dir = opendir ("/home/affan/modul2/hatiku/")) != NULL) {
    while ((rent = readdir(dir))!=NULL){
	strcpy(file, rent->d_name);
	struct stat st={0};
	struct passwd *owner = getpwuid(st.st_uid);
	struct group *group = getgrgid(st.st_gid);
	if (strcmp(file,"elen.ku")==0 && strcmp(owner->pw_name,"www-data")==0 && strcmp(group->gr_name,"www-data")==0){
	printf("%s %s\n",owner->pw_name,group->gr_name);
	chmod(file,0777);
	remove(file);
	}
	}
    closedir(dir);
    }
    sleep(3);
  }
  exit(EXIT_SUCCESS);
}
