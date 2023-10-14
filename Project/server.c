
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>
#include<time.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "file_structures.h"
#include "./getters_and_setters/read_write.h"
#include "./getters_and_setters/validity.h"
#include "./getters_and_setters/getset_student.h"
#include "./getters_and_setters/getset_faculty.h"
#include "./getters_and_setters/getset_course.h"
#include "./getters_and_setters/getset_admin.h"

#include "./handles/view.h"
#include "./handles/modify.h"
#include "./handles/menu.h"
#include "./handles/login.h"

void my_server_handle(int );

void main()
{
	struct sockaddr_in saddr, caddr;
	
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sfd==-1)
	{
		perror("Error while creating socket: ");
		exit(1);
	}

	printf("client side: socket created successfully \n");

	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(8083);
	
	int bind_status=bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
	if(bind_status==-1)
	{ 
		perror("Error while binding: ");
		exit(1);
	}
	printf("Binding to socket is successful\n");

	int listen_status=listen(sfd,2);
	if(listen_status==-1)
	{ 
		perror("Error while trying to listen for connections: ");
		exit(1);

	}

	int clientSize;
	while(1)
	{
		//Accept Connection
		clientSize=(int)sizeof(caddr);
		int cfd=accept(sfd,(struct sockaddr *)&caddr,&clientSize);
	
		if(cfd==-1)
		{ 
			perror("Error while accepting connection: ");
			close(sfd);
			exit(1);
		}

		if(!fork())
		{
			my_server_handle(cfd);
			close(cfd);
			exit(0);
		}

	}
	close(sfd);
}

void my_server_handle(int cfd)
{
	int readBytes, writeBytes;
	int choice;
	struct message msg;
	write_msg(cfd,1,0,"\n.....................Welcome to Academia....................... \nLogin Type\nEnter Your Choice { 1.Admin , 2.Student, 3.Faculty } : ");
	read_msg(cfd,&msg);
	choice=atoi(msg.body);
	
	switch(choice)
	{
		case 1:
			login_handle(cfd,0);
			break;
		case 2:
			login_handle(cfd,1);
			break;
		case 3:
			login_handle(cfd,2);
			break;
		default:
			write_msg(cfd,0,0,"");
			break;
	}
}
