#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>


struct course get_course_details(int course_id)
{
	int rBytes,wBytes, fd, offset;
	struct course my_course;
	//check validity of course_id
	if(is_validId(0,course_id))
	{
		fd=open("./records/course_file",O_RDONLY);
		if(fd==-1)
		{
			perror("Cannot Open File");
			return (struct course){-1,"NULL",0,0,0,0,0};
		}
		offset=lseek(fd,course_id*sizeof(struct course),SEEK_SET);
		if(offset==-1)
		{
			perror("Error while Repositioning in course File");
			return (struct course){-1,"NULL",0,0,0,0,0};

		}

		/*Setting Lock*/
		struct flock lock = {F_RDLCK, SEEK_SET, course_id*sizeof(struct course), sizeof(struct course), getpid()};
		int lockingStatus = fcntl(fd, F_SETLKW, &lock);
		if (lockingStatus == -1)
		{
			perror("Error obtaining read lock on course record!");
			return (struct course){-1,"NULL",0,0,0,0,0};
		}
		
		//critical section
		rBytes=read(fd,&my_course,sizeof(my_course));

		/*Unlocking....*/
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		if(rBytes<=0)
		{
			perror("Cannot read the file");
			return (struct course){-1,"NULL",0,0,0,0,0};
		}
		close(fd);
	}
	else
	{
		printf("Record Not Exists\n");
		return (struct course){-1,"NULL",0,0,0,0,0};
	}
	//success...
	return my_course;
}

/* Setter Program */

bool set_course_details(int course_id, struct course *my_course)
{
	int rBytes,wBytes, fd, offset;

	if(is_validId(0,course_id))
	{
	my_course->course_id=course_id;
	fd=open("./records/course_file",O_WRONLY);
	if(fd==-1)
	{
		perror("Cannot Open File");
		return 0;
	}
	offset=lseek(fd,course_id*sizeof(struct course),SEEK_SET);
	if(offset==-1)
	{
		perror("Error while Repositioning in course File");
		return 0;
	}
	
	/*Setting Lock*/
	struct flock lock = {F_WRLCK, SEEK_SET, course_id*sizeof(struct course), sizeof(struct course), getpid()};
	int lockingStatus = fcntl(fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
		perror("Error obtaining read lock on course record!");
		return 0;
	}
	
	//crirical section
	wBytes=write(fd,&(*my_course),sizeof(*my_course));

	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	if(wBytes<=0)
	{
		perror("Cannot write into the file");
		return 0;
	}
	close(fd);
	}
	else
	{
		printf("Record Not Exists\n");
		return 0;
	}

	//success...
	return 1;
}



int save_course(struct course *my_course)
{
	int course_id;
	int rBytes,wBytes, fd, offset;
	//set available course_id...
	course_id=get_record_details(0);
	if(course_id==-1) return -1;

	my_course->course_id=course_id;

	fd=open("./records/course_file",O_WRONLY | O_CREAT,0777);
	if(fd==-1)
	{
		perror("Cannot Open File");
		return -1;
	}
	offset=lseek(fd,course_id*sizeof(struct course),SEEK_SET);
	if(offset==-1)
	{
		perror("Error while Repositioning in course File");
		return -1;
	}

	/*Setting Lock: Mandatory*/
	struct flock lock = {F_WRLCK, SEEK_SET, 0,0, getpid()};
	int lockingStatus = fcntl(fd, F_SETLKW, &lock);
	if (lockingStatus == -1)
	{
		perror("Error obtaining read lock on course record!");
		return 0;
	}

	//crirical section
	wBytes=write(fd,&(*my_course),sizeof(*my_course));

	/*Unlocking....*/
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	if(wBytes<=0)
	{
		perror("Cannot write into the file");
		return -1;
	}
	close(fd);

	//upadate available account-no...
	if(!set_record_details(0,course_id+1))
	{
		printf("Error while updating record file\n");
		return -1;
	}
	//success...
	return course_id;
}
