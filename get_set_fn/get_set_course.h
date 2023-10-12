#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include "../headers.h"

int main()
{
	//get course details
	struct course get_course_details(int c_id)
	{
		int fd, bytes_read, bytes_write, offset;
		
		struct course C;
		
		fd = open("../records/course.txt", O_RDONLY);
		if(fd == -1)
		{
			perror("Unable to open file");
			return (struct course){-1,"NULL",-1,0,0,0};
		}

		offset = lseek(fd, c_id*(sizeof(struct course)), SEEK_SET);
		if(offset == -1)
		{
			perror(" ");
			return (struct course){-1,"NULL",-1,0,0,0};
		}

		//Locking
		struct flock lock;

		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
    	   	lock.l_start = c_id*(sizeof(struct course));
 	      	lock.l_len = sizeof(struct course);
       		lock.l_pid = getpid();

		int ret = fcntl(fd, F_SETLKW, &lock);
		if(ret == -1)
		{
			perror("Error in locking..\n");
			return (struct course){-1,"NULL",-1,0,0,0};
		}
		
		//critical section
		bytes_read = read(fd, &C, sizeof(C));

		//unlocking
		lock.l_type = F_UNLCK;
       		fcntl(fd, F_SETLK, &lock);

		if(bytes_read <= 0)
		{
			perror("Failed reading the record..\n");
			return (struct course){-1,"NULL",-1,0,0,0};
                }
		
		close(fd);
		return C;
	}

	//update course details
	int set_course_details(int cid, struct course *C)
	{
		int fd, bytes_read, bytes_write, offset;

		//call by ref
		C->course_id = cid;

		fd = open("../records/course.txt", O_WRONLY);

		if(fd == -1)
		{
			perror("Cannot open file..\n");
			return 0;
		}

		offset = lseek(fd, cid*sizeof(struct course), SEEK_SET);
		if(offset == -1)
		{
			perror(" ");
			return 0;
		}

		//Locking
                struct flock lock;

                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = cid*(sizeof(struct course));
                lock.l_len = sizeof(struct course);
                lock.l_pid = getpid();

                int ret = fcntl(fd, F_SETLKW, &lock);
                if(ret == -1)
                {
                        perror("Error in locking..\n");
                        return 0;
                }

		//critical section
		bytes_write = write(fd, &(*C), sizeof(*C));

		//unlocking
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);

                if(bytes_write <= 0)
                {
                        perror("Failed writing the record..\n");
                        return 0;
                }

                close(fd);
		return 1;
	}

	//Add new Course
	int save_new_course(struct course *C)
	{
		int cid;
		int fd, bytes_read, bytes_write, offset;

		//get id of next course
		struct record rec;
		int fd1;
		fd1 = open("../records/record.txt", O_RDONLY);
		lseek(fd1, 0, SEEK_SET);
		read(fd1, &rec, sizeof(rec));
		cid = rec.next_course;
		close(fd1);
		

		C->course_id = cid;

		fd = open("../records/course.txt", O_WRONLY | O_CREAT, 0777);

                if(fd == -1)
                {
                        perror("Cannot open file..\n");
                        return -1;
                }

                offset = lseek(fd, cid*sizeof(struct course), SEEK_SET);
                if(offset == -1)
                {
                        perror(" ");
                        return -1;
                }

                //Locking
                struct flock lock;

                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = cid*(sizeof(struct course));
                lock.l_len = sizeof(struct course);
                lock.l_pid = getpid();

                int ret = fcntl(fd, F_SETLKW, &lock);
                if(ret == -1)
                {
                        perror("Error in locking..\n");
                        return 0;
                }

		//critical section
                bytes_write = write(fd, &(*C), sizeof(*C));

                //unlocking
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);

                if(bytes_write <= 0)
                {
                        perror("Failed writing the record..\n");
                        return 0;
                }

                close(fd);
                return 1;
	}
}
		

