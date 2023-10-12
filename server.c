#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<time.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "headers.h"
#include "./get_set_fn/get_set_admin.h"
#include "./get_set_fn/get_set_course.h"
#include "./get_set_fn/get_set_faculty.h"
#include "./get_set_fn/get_set_stud.h"
#include "./handles/add.h"
#include "./handles/modify.h"
#include "./handles/menu.h"
#include "./handles/login.h"

void server_handle(int fd)
{
	int ch;


void main()
{
	struct sockaddr_in server, client;

        int sd, client_size, fd, bind_status, listen_status;
        char buf[80];

        sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sd == -1)
	{
		perror("Error in socket creation..\n");
		exit(1);
	}

	printf("\nServer : Socket creation successful..\n");

        server.sin_family = AF_UNIX;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(5555);

        bind_status = bind(sd, (struct sockaddr *)(&server), sizeof(server));
	if(bind_status == -1)
	{
		perror("\nError in binding..\n");
		exit(1);
	}

	printf("\nBinding successful..\n");

        listen_status = listen(sd, 5);
	if(listen_status == -1)
	{
		perror("Error in listening to connections..\n");
		exit(1);
	}
	
	while(1)
	{

        	client_size = (int)sizeof(client);
	
		fd = accept(sd, (struct sockaddr *)(&client), &client_size);
		if(fd == -1)
		{
			perror("Error in accepting connection..\n");
			exit(1);
		}

		printf("\nConnection accepted..\n");

		if(!fork()) //child
		{
			server_handle(fd);
			close(fd);
			exit(0);
		}
	}
	close(sd);
}
