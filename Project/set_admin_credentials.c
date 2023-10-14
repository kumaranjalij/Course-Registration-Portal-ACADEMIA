#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include"file_structures.h"


void main()
{
	struct administrator my_admin;
	int fd,writeBytes;
	fd=open("./records/admin_file",O_CREAT | O_RDWR,0777);
	if(fd==-1)
	{
		perror("Cannot Open File");
		exit(1);
	}

	//Set credentials
	my_admin.id=0;
	strcpy(my_admin.name,"Anjali J Kumar");
	strcpy(my_admin.login_id,"admin");
	strcpy(my_admin.password,"admin1");
	writeBytes=write(fd,&my_admin,sizeof(my_admin));
	
	if(writeBytes<=0)
	{
		perror("Cannot write into file");
		exit(1);
	}
	close(fd);
}
