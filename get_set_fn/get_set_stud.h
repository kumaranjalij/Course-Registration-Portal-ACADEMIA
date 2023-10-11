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
	struct student get_stud_details(int stud_id)
	{
		int fd, bytes_read, bytes_write, offset;

		struct student stud;

		

