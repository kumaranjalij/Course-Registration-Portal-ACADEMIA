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
        //get faculty  details
        struct faculty get_fac_details(int fac_id)
        {
                int fd, bytes_read, bytes_write, offset;

                struct faculty fac;

                fd = open("../records/faculty.txt", O_RDONLY);
                if(fd == -1)
                {
                        perror("Unable to open file");
                        return (struct faculty){-1,"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0};
                }

                offset = lseek(fd, fac_id*(sizeof(struct faculty)), SEEK_SET);
                if(offset == -1)
                {
                        perror(" ");
			return (struct faculty){-1,"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0};
                }

                //Locking
                struct flock lock;

                lock.l_type = F_RDLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = fac_id*(sizeof(struct faculty));
                lock.l_len = sizeof(struct faculty);
                lock.l_pid = getpid();

                int ret = fcntl(fd, F_SETLKW, &lock);
                if(ret == -1)
                {
                        perror("Error in locking..\n");
			return (struct faculty){-1,"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0};
                }

                //critical section
                bytes_read = read(fd, &fac, sizeof(fac));

                //unlocking
                lock.l_type = F_UNLCK;
                fcntl(fd, F_SETLK, &lock);

                if(bytes_read <= 0)
                {
                        perror("Failed reading the record..\n");
               		return (struct faculty){-1,"NULL","NULL","NULL","NULL","NULL","NULL",{0,0,0},0,0};
	       	}

                close(fd);
      		return fac;
      	}
      

        //update faculty details
        int set_fac_details(int facid, struct faculty *fac)
        {
                int fd, bytes_read, bytes_write, offset;

                //call by ref
                fac->fac_id = facid;

                fd = open("../records/faculty.txt", O_WRONLY);

                if(fd == -1)
                {
                        perror("Cannot open file..\n");
                        return 0;
                }

                offset = lseek(fd, facid*sizeof(struct faculty), SEEK_SET);
                if(offset == -1)
                {
                        perror(" ");
                        return 0;
                }

		//Locking
                struct flock lock;

                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = facid*(sizeof(struct faculty));
                lock.l_len = sizeof(struct faculty);
                lock.l_pid = getpid();

                int ret = fcntl(fd, F_SETLKW, &lock);
                if(ret == -1)
                {
                        perror("Error in locking..\n");
                        return 0;
                }

                //critical section
                bytes_write = write(fd, &(*fac), sizeof(*fac));

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
	
	//Save new faculty
        int save_new_faculty(struct faculty *fac)
        {
                int facid;
                int fd, bytes_read, bytes_write, offset;

                //get id of next faculty
                struct record rec;
                int fd1;
                fd1 = open("../records/record.txt", O_RDONLY);
                lseek(fd1, 0, SEEK_SET);
                read(fd1, &rec, sizeof(rec));
                facid = rec.next_fac;
                close(fd1);


                fac->fac_id = facid;

                fd = open("../records/faculty.txt", O_WRONLY | O_CREAT, 0777);

                if(fd == -1)
                {
                        perror("Cannot open file..\n");
                        return -1;
                }

                offset = lseek(fd, facid*sizeof(struct faculty), SEEK_SET);
                if(offset == -1)
                {
                        perror(" ");
                        return -1;
                }
		
		 //Locking
                struct flock lock;

                lock.l_type = F_WRLCK;
                lock.l_whence = SEEK_SET;
                lock.l_start = facid*(sizeof(struct faculty));
                lock.l_len = sizeof(struct faculty);
                lock.l_pid = getpid();

                int ret = fcntl(fd, F_SETLKW, &lock);
                if(ret == -1)
                {
                        perror("Error in locking..\n");
                        return 0;
                }

                //critical section
                bytes_write = write(fd, &(*fac), sizeof(*fac));

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

