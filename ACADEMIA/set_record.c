#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

struct record{
	int total_n_students;
	int total_n_faculty;
	int total_n_courses;
	int next_student;
	int next_faculty;
	int next_course;
};

int main(){

struct record firstRecord;

int fd = open("./Record_File/record.txt", O_CREAT | O_RDWR, 0777);
if(fd==-1){
	perror("Cannot Open File ");
	exit(0);
}
struct flock mylock = {mylock.l_type = F_WRLCK, mylock.l_whence = SEEK_SET, mylock.l_start = 0, mylock.l_len = 0, mylock.l_pid = getpid()};

int wrlock = fcntl(fd, F_SETLKW, &mylock);
if(wrlock==-1){
	perror("Failed to acquire lock ");
	exit(0);
}

firstRecord.total_n_students = 0;
firstRecord.total_n_faculty = 0;
firstRecord.total_n_courses = 0;
firstRecord.next_student = 1;
firstRecord.next_faculty = 1;
firstRecord.next_course = 1;

int writeBytes=write(fd,&firstRecord,sizeof(firstRecord));

if(writeBytes<=0){
	perror("Cannot write into file");
	exit(1);
}

mylock.l_type = F_UNLCK;
int unlock = fcntl(fd, F_SETLK, &mylock);
if(unlock==-1){
	perror("Unlocking failed ");
	exit(0);
}
printf("Initialized record structure sucessfully... \n");
close(fd);
return 0;
}
