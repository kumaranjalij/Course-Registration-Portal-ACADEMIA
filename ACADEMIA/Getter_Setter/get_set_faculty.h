#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int set_new_faculty(struct faculty *new_f){
	int faculty_id, total;
	int rd, wt, fd, offset;
	faculty_id=get_next_record(1);
	total = get_all_record(1);
	if(faculty_id==-1) return -1;
	new_f->f_id=faculty_id;
	sprintf(new_f->f_login_id,"IIITB%d",faculty_id);
	sprintf(new_f->f_password,"IIITB%d",faculty_id);

	fd=open("./Record_File/faculty.txt",O_WRONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,(faculty_id-1)*sizeof(struct faculty),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in faculty File ");
		return -1;
	}
	/*Setting Lock*/
	struct flock mylock = {F_WRLCK, SEEK_SET, (faculty_id-1)*sizeof(struct faculty), sizeof(struct faculty), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return -1;
	}
	/*...........*/
	wt=write(fd,&(*new_f),sizeof(*new_f));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &mylock);
	/*...........*/
	if(wt<=0){
		perror("Cannot write into the file");
		return -1;
	}
	close(fd);

	//upadate available account-no...
	int set1 = set_next_record(1,faculty_id+1);
	int set2 = set_all_record(1, total+1);
	if(set1!=1 && set2!=1){
		printf("Error while updating record file\n");
		return -1;
	}

	//success...
	return faculty_id;
}

struct faculty get_faculty(int faculty_id){
	int rd, fd, offset;
	struct faculty fac;

	fd=open("./Record_File/faculty.txt",O_RDONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return (struct faculty){0, "NULL", '\0', "NULL", "NULL", "NUL", "NULL", "NULL", {0,0,0}, 0, 0, 0};
	}
	offset=lseek(fd,(faculty_id-1)*sizeof(struct faculty),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in faculty File ");
		return (struct faculty){0, "NULL", '\0', "NULL", "NULL", "NUL", "NULL", "NULL", {0,0,0}, 0, 0, 0};
	}
	/*Setting Lock*/
	struct flock mylock = {F_RDLCK, SEEK_SET, (faculty_id-1)*sizeof(struct faculty), sizeof(struct faculty), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return (struct faculty){0, "NULL", '\0', "NULL", "NULL", "NUL", "NULL", "NULL", {0,0,0}, 0, 0, 0};
	}
	/*...........*/
	rd=read(fd,&fac,sizeof(fac));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &mylock);
	/*...........*/
	if(rd<=0){
		perror("Cannot write into the file");
		return (struct faculty){0, "NULL", '\0', "NULL", "NULL", "NUL", "NULL", "NULL", {0,0,0}, 0, 0, 0};
	}
	close(fd);

	//success...
	return fac;
}

int set_faculty(int faculty_id, struct faculty *new_f){
	int wt, fd, offset;

	fd=open("./Record_File/faculty.txt",O_WRONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,(faculty_id-1)*sizeof(struct faculty),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in faculty File ");
		return -1;
	}
	/*Setting Lock*/
	struct flock mylock = {F_WRLCK, SEEK_SET, (faculty_id-1)*sizeof(struct faculty), sizeof(struct faculty), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return -1;
	}
	/*...........*/
	wt=write(fd,&(*new_f),sizeof(*new_f));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &mylock);
	/*...........*/
	if(wt<=0){
		perror("Cannot write into the file");
		return -1;
	}
	close(fd);

	//success...
	return 1;
}
