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

#define _GNU_SOURCE

#include "file_structures.h"
#include "my_function.h"
#include "./Libs/main_menu.h"
#include "./Libs/login.h"
#include "./Libs/student_func.h"
#include "./Libs/faculty_func.h"
#include "./Libs/course_func.h"
#include "./Getter_Setter/record_set.h"
//#include "./Getter_Setter/get_set_record.h"
#include "./Getter_Setter/get_set_student.h"
#include "./Getter_Setter/get_set_faculty.h"
#include "./Getter_Setter/get_set_course.h"
#include "./Getter_Setter/cfd_read_write.h"

void my_server_handle(int );
void main(){
struct sockaddr_in saddr, caddr;
//create socket
int sfd=socket(AF_INET,SOCK_STREAM,0);
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
int bind_status=bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
if(bind_status==-1){ 
perror("Error while binding: ");
exit(1);
}
printf("Binding to socket is successful\n");
int listen_status=listen(sfd,2);
if(listen_status==-1){ 
perror("Error while trying to listen for connections: ");
exit(1);
}
int clientSize;
while(1){
//Accept Connection
clientSize=(int)sizeof(caddr);
int cfd=accept(sfd,(struct sockaddr *)&caddr,&clientSize);
//error
if(cfd==-1){ 
perror("Error while accepting connection: ");
close(sfd);
exit(1);
}
//successfully accepted request.
if(!fork()){
//write(1,"\nNew Client Connection Accepted\n",32);
my_server_handle(cfd);
//write(1,"\nClient Connection Terminated\n",30);
close(cfd);
exit(0);
}

}
close(sfd);
}

void my_server_handle(int cfd){
	menu(cfd);
}
