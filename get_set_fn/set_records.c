#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include "../headers.h"

int main()
{
	struct record rec;

	int fd, bytes_write;

	fd = open("../records/record.txt", O_CREAT | O_RDWR , 0777);
        if(fd == -1)
        {
                perror("File creation failed..\n");
                exit(1);
        }

	rec.total_stud = 0;
	rec.total_fac = 0;
	rec.total_courses = 0;

	rec.next_stud = 1;
        rec.next_fac = 1;
        rec.next_course = 1;

	bytes_write = write(fd, &rec, sizeof(rec));

	if(bytes_write <= 0);
	{
		perror(" ");
		exit(1);
	}

	close(fd);
}


