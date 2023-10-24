#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>

int get_all_record(int type);
int set_all_record(int type, int value);

int get_next_record(int type);
int set_next_record(int type, int value);

struct record{
	int total_student;
	int total_faculty;
	int total_course;
	int new_s;
	int new_f;
	int new_c;
};

int main(){

struct record firstRecord;

int fd = open("./Record_File/record.txt", O_CREAT | O_RDWR, 0777);
if(fd==-1){
	perror("Cannot Open File ");
	exit(0);
}
/*
int a = get_all_record(0);
int b = get_all_record(1);
int c = get_all_record(2);

printf("%d\n", a);
printf("%d\n", b);
printf("%d\n", c);


printf("%d\n", set_all_record(0, a+1));
printf("%d\n", set_all_record(1, b+1));
printf("%d\n", set_all_record(2, c+1));

printf("\n");
int d = get_next_record(0);
int e = get_next_record(1);
int f = get_next_record(2);

printf("%d\n", d);
printf("%d\n", e);
printf("%d\n", f);


printf("%d\n", set_next_record(0, d+1));
printf("%d\n", set_next_record(1, e+1));
printf("%d\n", set_next_record(2, f+1));

printf("\n");
*/
struct flock mylock = {mylock.l_type = F_RDLCK, mylock.l_whence = SEEK_SET, mylock.l_start = 0, mylock.l_len = 0, mylock.l_pid = getpid()};

int wrlock = fcntl(fd, F_SETLKW, &mylock);
if(wrlock==-1){
	perror("Failed to acquire lock ");
	exit(0);
}

int writeBytes=read(fd,&firstRecord,sizeof(firstRecord));

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

printf("%d\n",firstRecord.total_student);
printf("%d\n",firstRecord.total_faculty);
printf("%d\n",firstRecord.total_course);
printf("%d\n",firstRecord.new_s);
printf("%d\n",firstRecord.new_f);
printf("%d\n",firstRecord.new_c);


printf("Initialized record structure sucessfully... \n");
close(fd);
return 0;
}

int get_all_record(int type){
	struct record my_record;
	int record_fd,rBytes,retVal, offset;
	record_fd=open("./Record_File/record.txt",O_RDONLY);
	if(record_fd==-1){
	perror("Cannot Open File");
	return -1;
	}
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return -1;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(rBytes<=0){
	perror("Cannot read the file");
	return -1;
	}
	// Body.................
	switch(type){
	case 0: retVal=my_record.total_student;
		break;
	case 1: retVal=my_record.total_faculty;
		break;
	case 2: retVal=my_record.total_course;
		break;
	default: return -1;
		break;
	}

	close(record_fd);
	return retVal;
}

int set_all_record(int type, int value){
	struct record my_record;
	int record_fd,rBytes,wBytes, offset;
	//open...
	record_fd=open("./Record_File/record.txt",O_RDWR);
	if(record_fd==-1){
	perror("Cannot Open File");
	return 0;
	}
	//read...
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/

	if(rBytes<=0){
	perror("Cannot read the file");
	return 0;
	}
	// Body.................
	switch(type){
	case 0: my_record.total_student=value;
		break;
	case 1: my_record.total_faculty=value;
		break;
	case 2: my_record.total_course=value;
		break;
	default: return 0;
		break;
	}
	//update....
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	lock.l_type = F_WRLCK;
	lock.l_start = 0*sizeof(struct record);
	lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on record!");
	return 0;
	}
	/*...........*/
	wBytes=write(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(wBytes<=0){
	perror("Cannot write into the file");
	return 0;
	}

	close(record_fd);
	return 1;
}

int get_next_record(int type){
	struct record my_record;
	int record_fd,rBytes,retVal, offset;
	record_fd=open("./Record_File/record.txt",O_RDONLY);
	if(record_fd==-1){
	perror("Cannot Open File");
	return -1;
	}
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return -1;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(rBytes<=0){
	perror("Cannot read the file");
	return -1;
	}
	// Body.................
	switch(type){
	case 0: retVal=my_record.new_s;
		break;
	case 1: retVal=my_record.new_f;
		break;
	case 2: retVal=my_record.new_c;
		break;
	default: return -1;
		break;
	}

	close(record_fd);
	return retVal;
}

int set_next_record(int type, int value){
	struct record my_record;
	int record_fd,rBytes,wBytes, offset;
	//open...
	record_fd=open("./Record_File/record.txt",O_RDWR);
	if(record_fd==-1){
	perror("Cannot Open File");
	return 0;
	}
	//read...
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	struct flock lock = {F_RDLCK, SEEK_SET, 0*sizeof(struct record), sizeof(struct record), getpid()};
	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on Account record!");
	return 0;
	}
	/*...........*/
	rBytes=read(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/

	if(rBytes<=0){
	perror("Cannot read the file");
	return 0;
	}
	// Body.................
	switch(type){
	case 0: my_record.new_s=value;
		break;
	case 1: my_record.new_f=value;
		break;
	case 2: my_record.new_c=value;
		break;
	default: return 0;
		break;
	}
	//update....
	offset=lseek(record_fd,0*sizeof(struct record),SEEK_SET);
	if(offset==-1){
	perror("Error while Repositioning in Record File");
	return 0;
	}

	/*Setting Lock*/
	lock.l_type = F_WRLCK;
	lock.l_start = 0*sizeof(struct record);
	lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
	perror("Error obtaining read lock on record!");
	return 0;
	}
	/*...........*/
	wBytes=write(record_fd,&my_record,sizeof(my_record));
	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(record_fd, F_SETLK, &lock);
	/*...........*/
	if(wBytes<=0){
	perror("Cannot write into the file");
	return 0;
	}

	close(record_fd);
	return 1;
}

