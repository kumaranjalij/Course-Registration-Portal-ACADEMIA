#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>

void client_handle(int sd)
{

}

void main()
{
	struct sockaddr_in server;

	int sd, status;
	char buf[1024];

	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sd == -1)
	{
		perror("Error in socket creation..\n");
		exit(1);
	}

	printf("Client : Socket creation successful..\n");

	server.sin_family = AF_UNIX;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(5555);

	//connect to server
        status = connect(sd, (struct sockaddr *)(&server), sizeof(server));
	if(status == -1)
	{
		perror("Connection to server failed..\n");
                exit(1);
        }

	printf("Client Server connection established ..\n");

	client_handle(sd);
	close(sd);
}

	

