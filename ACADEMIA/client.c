#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>

struct message{
	int id;
	int type;
	int action;
	char body[1000];
};

void my_client_handle(int sfd);
void main()
{
//create socket address structure
struct sockaddr_in saddr;
int sfd, status;
//create socket
sfd=socket(AF_INET,SOCK_STREAM,0);
//error
if(sfd==-1){
perror("Error while creating socket: ");
exit(1);
}
//successfully created socket.
printf("client side: socket created successfully \n");
//Set Address fields.
saddr.sin_addr.s_addr=htonl(INADDR_ANY);

saddr.sin_family=AF_INET;
saddr.sin_port=htons(8083);
//Connect to server.
status=connect(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
//error
if(status==-1){ 
perror("Error while connecting to server: ");
exit(1);
}
//successfully connected to server.
printf("client to server connection successfully established\n");

//Communication
my_client_handle(sfd);
//End of communication
close(sfd);
}

void my_client_handle(int sfd){
	char *end="";
	int readBytes, writeBytes;
	struct message msg;
	msg.id=0;
	int itr=1;
	while(itr){
		readBytes=read(sfd,&msg,sizeof(msg));

		/*
		check if it is a (0)control Message or (1)Data Message...
		*/
		if(msg.type==0){
			//control Message
			if(msg.action==0){//Exit Signal
				end="\nExit Signal Received from Server\nExiting...\n";
				write(1,end,strlen(end));
				return;
			}
			else if(msg.action==1){//Ignore Read from STDIN and write to the server...
				write(1,msg.body,strlen(msg.body));
			}
			else return;
		}
		else if(msg.type==1){
			//Data Message
			if(msg.action==0){//Reply Type: int/char/bool (one word)...
				write(1,msg.body,strlen(msg.body));
				msg.id=itr;
				char temp[1000];
				read(0,temp,sizeof(temp));
				bzero(msg.body,sizeof(msg.body));
				int i=0;
				while(temp[i]!=' ' && temp[i]!='\n' && temp[i]!='\0')
				{
					msg.body[i]=temp[i];
					i++;
				}
				msg.body[i]='\0';
				writeBytes=write(sfd,&msg,sizeof(msg));

			}

			else if(msg.action==1){//Reply Type: string (one sentence)...
				write(1,msg.body,strlen(msg.body));
				msg.id=itr;
				char temp[1000];
				read(0,temp,sizeof(temp));
				bzero(msg.body,sizeof(msg.body));
				int i=0;
				while(temp[i]!='\n' && temp[i]!='\0')
				{
					msg.body[i]=temp[i];
					i++;
				}
				msg.body[i]='\0';

				writeBytes=write(sfd,&msg,sizeof(msg));
			}
			else{//Reply Type: password...
				char temp[1000];
				strcpy(temp, getpass(msg.body));
				msg.id=itr;
				msg.type=1;
				msg.action=1;
				bzero(msg.body,sizeof(msg.body));
				strcpy(msg.body,temp);
				msg.body[strlen(temp)]=='\0';
				writeBytes=write(sfd,&msg,sizeof(msg));
			}

		}
		else{
			end="Invalid Message Structure sent by Server\nExiting...\n";
			write(1,end,strlen(end));
			return;
		}
		itr++;
	}//end of infinite while loop...
}
