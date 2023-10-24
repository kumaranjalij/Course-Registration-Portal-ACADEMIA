#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int set_new_student(struct student *new_stud){
	int student_id, total;
	int rd, wt, fd, offset;
	student_id=get_next_record(0);
	total = get_all_record(0);
	if(student_id==-1) return -1;
	new_stud->s_id=student_id;
	sprintf(new_stud->s_login_id,"MT2023%d",student_id);
	sprintf(new_stud->s_password,"MT2023%d",student_id);

	fd=open("./Record_File/student.txt",O_WRONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,(student_id-1)*sizeof(struct student),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in student File ");
		return -1;
	}
	/*Setting Lock*/
	struct flock mylock = {F_WRLCK, SEEK_SET, (student_id-1)*sizeof(struct student), sizeof(struct student), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return -1;
	}
	/*...........*/
	wt=write(fd,&(*new_stud),sizeof(*new_stud));
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
	
	int set1 = set_next_record(0, student_id+1);
	int set2 = set_all_record(0, total+1);

	//success...
	return student_id;
}

struct student get_student(int student_id){
	int rd, fd, offset;
	struct student stud;

	fd=open("./Record_File/student.txt",O_RDONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return (struct student){0, "NULL", '\0', "NULL", "NULL", "NULL", "NULL", {0,0,0,0,0}, 0, 0, 0};
	}
	offset=lseek(fd,(student_id-1)*sizeof(struct student),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in student File ");
		return (struct student){0, "NULL", '\0', "NULL", "NULL", "NULL", "NULL", {0,0,0,0,0}, 0, 0, 0};
	}
	/*Setting Lock*/
	struct flock mylock = {F_RDLCK, SEEK_SET, (student_id-1)*sizeof(struct student), sizeof(struct student), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return (struct student){0, "NULL", '\0', "NULL", "NULL", "NULL", "NULL", {0,0,0,0,0}, 0, 0, 0};
	}
	/*...........*/
	rd=read(fd,&stud,sizeof(stud));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &mylock);
	/*...........*/
	if(rd<=0){
		perror("Cannot write into the file");
		return (struct student){0, "NULL", '\0', "NULL", "NULL", "NULL", "NULL", {0,0,0,0,0}, 0, 0, 0};
	}
	close(fd);

	//success...
	return stud;
}

int set_student(int student_id, struct student *new_stud){
	int wt, fd, offset;

	fd=open("./Record_File/student.txt",O_WRONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,(student_id-1)*sizeof(struct student),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in student File ");
		return -1;
	}
	/*Setting Lock*/
	struct flock mylock = {F_WRLCK, SEEK_SET, (student_id-1)*sizeof(struct student), sizeof(struct student), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return -1;
	}
	/*...........*/
	wt=write(fd,&(*new_stud),sizeof(*new_stud));
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
