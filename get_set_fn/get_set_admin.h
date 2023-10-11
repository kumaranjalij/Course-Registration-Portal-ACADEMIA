#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include "../headers.h"

int main()
{
	struct admin get_admin_details()
	{
		struct admin ad;

		int fd, bytes_read;
		fd = ("../records/admin.txt", O_RDONLY);
		if(fd == -1)
		{
			perror("Failed to open file..\n");
			exit(1);
		}

		//read admin credentials from file
		bytes_read = read(fd, &ad, sizeof(ad));
		if(bytes_read > 0)
			return ad;
	}

	return 0;
}

