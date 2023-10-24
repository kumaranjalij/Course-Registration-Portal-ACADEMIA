#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

int set_new_course(struct course *new_course){
	int course_id, total;
	int rd, wt, fd, offset;
	course_id=get_next_record(2);
	total = get_all_record(2);
	if(course_id==-1) return -1;
	new_course->c_id=course_id;

	fd=open("./Record_File/course.txt",O_WRONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,(course_id-1)*sizeof(struct course),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in customer File ");
		return -1;
	}
	/*Setting Lock*/
	struct flock mylock = {F_WRLCK, SEEK_SET, (course_id-1)*sizeof(struct course), sizeof(struct course), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return -1;
	}
	/*...........*/
	wt=write(fd,&(*new_course),sizeof(*new_course));
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
	int set1 = set_next_record(2,course_id+1);
	int set2 = set_all_record(2, total+1); 
	if(set1!=1 && set2!=1){
		printf("Error while updating record file\n");
		return -1;
	}

	//success...
	return course_id;
}

struct course get_course(int course_id){
	int rd, fd, offset;
	struct course cour;

	fd=open("./Record_File/course.txt",O_RDONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return (struct course){0, "NULL", 0, 0, 0, 0, 0};
	}
	offset=lseek(fd,(course_id-1)*sizeof(struct course),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in course File ");
		return (struct course){0, "NULL", 0, 0, 0, 0, 0};
	}
	/*Setting Lock*/
	struct flock mylock = {F_RDLCK, SEEK_SET, (course_id-1)*sizeof(struct course), sizeof(struct course), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return (struct course){0, "NULL", 0, 0, 0, 0, 0};
	}
	/*...........*/
	rd=read(fd,&cour,sizeof(cour));
	/*Unlocking....*/
	mylock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &mylock);
	/*...........*/
	if(rd<=0){
		perror("Cannot write into the file");
		return (struct course){0, "NULL", 0, 0, 0, 0, 0};
	}
	close(fd);

	//success...
	return cour;
}

int set_course(int course_id, struct course *new_course){
	int wt, fd, offset;

	fd=open("./Record_File/course.txt",O_WRONLY | O_CREAT, 0777);
	if(fd==-1){
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,(course_id-1)*sizeof(struct course),SEEK_SET);
	if(offset==-1){
		perror("Error while Repositioning in customer File ");
		return -1;
	}
	/*Setting Lock*/
	struct flock mylock = {F_WRLCK, SEEK_SET, (course_id-1)*sizeof(struct course), sizeof(struct course), getpid()};
	int lock = fcntl(fd, F_SETLKW, &mylock);
	if (lock == -1)
	{
		perror("Error obtaining lock!");
		return -1;
	}
	/*...........*/
	wt=write(fd,&(*new_course),sizeof(*new_course));
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
