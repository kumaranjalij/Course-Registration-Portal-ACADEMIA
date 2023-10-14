#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>

struct administrator get_admin_details(int id)
{
	struct administrator my_admin;
	int fd,rBytes;
	fd=open("./records/admin_file",O_RDONLY);
	if(fd==-1)
	{
		perror("Cannot Open File");
		exit(1);
	}
	
	//GET credentials
	int offset=lseek(fd,id*sizeof(struct administrator),SEEK_SET);
	if(offset != -1)
	{
		/*Setting Lock*/
		struct flock lock = {F_RDLCK, SEEK_SET, id*sizeof(struct administrator), sizeof(struct administrator), getpid()};
		int lockingStatus = fcntl(fd, F_SETLKW, &lock);
		if (lockingStatus == -1)
		{
			perror("Error obtaining read lock on Account record!");
			return (struct administrator) {-1,"NULL","NULL","NULL"};
		}

		//critical section
		rBytes=read(fd,&my_admin,sizeof(my_admin));
	
		/*Unlocking....*/
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		if(rBytes>0)
		{
			return my_admin;
		}
	}
	return (struct administrator) {-1,"NULL","NULL","NULL"};
}
