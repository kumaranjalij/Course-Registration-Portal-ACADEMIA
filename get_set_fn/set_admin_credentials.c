#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include "../headers.h"

int main()
{
        struct admin ad;

        int fd, bytes_write;

        fd = open("../records/admin.txt", O_CREAT | O_RDWR , 0777);
        if(fd == -1)
        {
                perror("File creation failed..\n");
                exit(1);
        }

	strcpy(ad.admin_name,"Anjali J Kumar");
	strcpy(ad.login_id,"iiitb");
	strcpy(ad.passwd,"adminiiitb");

        bytes_write = write(fd, &ad, sizeof(ad));

        if(bytes_write <= 0);
        {
                perror(" ");
                exit(1);
        }

        close(fd);
}

