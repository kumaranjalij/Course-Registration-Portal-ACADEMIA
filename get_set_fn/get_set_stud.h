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
	//get student details
	struct student get_stud_details(int stud_id)
	{
		int fd, bytes_read, bytes_write, offset;
		
		struct student stud;
		
		fd = open("../records/stud.txt", O_RDONLY);
		if(fd == -1)
		{
			perror("Unable to open file");
			return (struct student){-1,"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0,},0,0};
		}

		offset = lseek(fd, stud_id*(sizeof(struct student)), SEEK_SET);
		if(offset == -1)
		{
			perror(" ");
			return (struct student){-1,"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0,},0,0};
		}

		//Locking
		struct flock lock;

		lock.l_type = F_RDLCK;
		lock.l_whence = SEEK_SET;
    	   	lock.l_start = stud_id*(sizeof(struct student));
 	      	lock.l_len = sizeof(struct student);
       		lock.l_pid = getpid();

		int ret = fcntl(fd, F_SETLKW, &lock);
		if(ret == -1)
		{
			perror("Error in locking..\n");
			return (struct student){-1,"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0,},0,0};
		}
		
		//critical section
		bytes_read = read(fd, &stud, sizeof(stud));

		//unlocking
		lock.l_type = F_UNLCK;
       		fcntl(fd, F_SETLK, &lock);

		if(bytes_read <= 0)
		{
			perror("Failed reading the record..\n");
			return (struct student){-1,"NULL","NULL","NULL","NULL","NULL",{0,0,0,0,0,},0,0};
                }
		
		close(fd);
		return stud;
	}

	//update student details
	int set_stud_details(int studid, struct student *stud)
	{
		int fd, bytes_read, bytes_write, offset;

		//call by ref
		stud->stud_id = studid;

		fd = open("../records/stud.txt", O_WRONLY);

		if(fd == -1)
		{
			perror("Cannot open file..\n");
			return 0;
		}

		offset = lseek(fd, studid*sizeof(struct student), SEEK_SET);
		if(offset == -1)
		{
			perror(" ");
			return 0;
		}

		//Locking
                struct flock lock;

                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = studid*(sizeof(struct student));
                lock.l_len = sizeof(struct student);
                lock.l_pid = getpid();

                int ret = fcntl(fd, F_SETLKW, &lock);
                if(ret == -1)
                {
                        perror("Error in locking..\n");
                        return 0;
                }

		//critical section
		bytes_write = write(fd, &(*stud), sizeof(*stud));

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

	//Save new student
	int save_new_student(struct student *stud)
	{
		int studid;
		int fd, bytes_read, bytes_write, offset;

		//get id of next student
		struct record rec;
		int fd1;
		fd1 = open("../records/record.txt", O_RDONLY);
		lseek(fd1, 0, SEEK_SET);
		read(fd1, &rec, sizeof(rec));
		studid = rec.next_stud;
		close(fd1);
		

		stud->stud_id = studid;

		fd = open("../records/stud.txt", O_WRONLY | O_CREAT, 0777);

                if(fd == -1)
                {
                        perror("Cannot open file..\n");
                        return -1;
                }

                offset = lseek(fd, studid*sizeof(struct student), SEEK_SET);
                if(offset == -1)
                {
                        perror(" ");
                        return -1;
                }

                //Locking
                struct flock lock;

                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = studid*(sizeof(struct student));
                lock.l_len = sizeof(struct student);
                lock.l_pid = getpid();

                int ret = fcntl(fd, F_SETLKW, &lock);
                if(ret == -1)
                {
                        perror("Error in locking..\n");
                        return 0;
                }

		//critical section
                bytes_write = write(fd, &(*stud), sizeof(*stud));

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
		
