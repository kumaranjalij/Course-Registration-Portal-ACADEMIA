#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>

struct administrator{
int id;
char name[25];
char login_id[10];
char password[10];
};

int main(){

struct administrator myadmin;

int fd = open("./Record_File/admin.txt", O_CREAT | O_RDWR, 0777);
if(fd==-1){
	perror("Cannot Open File ");
	exit(0);
}
struct flock mylock = {mylock.l_type = F_WRLCK, mylock.l_whence = SEEK_SET, mylock.l_start = 0, mylock.l_len = 0, mylock.l_pid = getpid()};

int wrlock = fcntl(fd, F_SETLKW, &mylock);
if(wrlock==-1){
	perror("Failed to acquire lock : ");
	exit(0);
}

myadmin.id=0;
strcpy(myadmin.name,"Anjali");
strcpy(myadmin.login_id,"admin");
strcpy(myadmin.password,"admin");
int writeBytes=write(fd,&myadmin,sizeof(myadmin));

if(writeBytes<=0){
	perror("Cannot write into file");
	exit(1);
}

mylock.l_type = F_UNLCK;
int unlock = fcntl(fd, F_SETLK, &mylock);
if(unlock==-1){
	perror("Unlocking failed : ");
	exit(0);
}
printf("Admin Created successful... \n");
printf("Login id : %s\n", myadmin.login_id);
printf("Password : %s\n", myadmin.password);
close(fd);
return 0;
}
