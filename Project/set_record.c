#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include "file_structures.h"

void main()
{
	struct record my_record;
	int fd,writeBytes;
	fd=open("./records/record_file",O_CREAT | O_RDWR,0777);
	if(fd==-1)
	{
		perror("Cannot Open File");
		exit(1);
	}

	//Set credentials
	my_record.total_n_students=0;
	my_record.total_n_faculty=0;
	my_record.total_n_courses=0;
	my_record.next_student=1;
	my_record.next_course=1;
	my_record.next_faculty=1;
	writeBytes=write(fd,&my_record,sizeof(my_record));
	if(writeBytes<=0)
	{
		perror("Cannot write into file");
		exit(1);
	}
	close(fd);
}

