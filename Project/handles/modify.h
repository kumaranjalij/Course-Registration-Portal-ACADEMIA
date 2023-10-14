void modify_student_password(int cfd, int id)
{
	struct student my_student;
	struct message msg;
	int readBytes, writeBytes;

	write_msg(cfd,1,2,"\nEnter/ Set New Password: # ");
	read_msg(cfd,&msg);

	my_student=get_student_details(id);
	if(my_student.stud_id==-1)
	{
		write_msg(cfd,0,1,"\nInvalid Student-Id...");
		return;
	}

	bzero(my_student.stud_password,sizeof(my_student.stud_password));
	strcpy(my_student.stud_password,msg.body);

	bool status=set_student_details(id,&my_student);
	if(status==0)
	{
		write_msg(cfd,0,1,"\nPassword Setting Failed...");
	}
	else
	{
		write_msg(cfd,0,1,"\nPassword Set Successfully...");
	}
}


void modify_faculty_password(int cfd, int id)
{
	struct faculty my_faculty;
	struct message msg;
	int readBytes, writeBytes;

	write_msg(cfd,1,2,"\nEnter/ Set New Password: # ");
	read_msg(cfd,&msg);

	my_faculty=get_faculty_details(id);
	if(my_faculty.faculty_id==-1)
	{
		write_msg(cfd,0,1,"\nInvalid Faculty-Id...");
		return;
	}

	bzero(my_faculty.faculty_password,sizeof(my_faculty.faculty_password));
	strcpy(my_faculty.faculty_password,msg.body);

	bool status=set_faculty_details(id,&my_faculty);
	if(status==0)
	{
		write_msg(cfd,0,1,"\nPassword Setting Failed...");
	}
	else
	{
		write_msg(cfd,0,1,"\nPassword Set Successfully...");
	}
}

void modify_student_details(int cfd)
{
	struct student my_student;
	struct message msg;
	int readBytes, writeBytes;

	write_msg(cfd,1,0,"\nEnter Student-Id: ");
	read_msg(cfd,&msg);
	int id=atoi(msg.body);
	
	my_student=get_student_details(id);
	if(my_student.stud_id==-1)
	{
		write_msg(cfd,0,1,"\nInvalid Student-Id...");
		return;
	}

	// Getting New Details
	write_msg(cfd,1,1,"\nEnter (New) Name: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_name,msg.body);

	write_msg(cfd,1,0,"\nEnter (New) Gender: ");
	read_msg(cfd,&msg);

	my_student.stud_gender=msg.body[0];

	write_msg(cfd,1,1,"\nEnter (New) Phone Number: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_phone,msg.body);
	
	write_msg(cfd,1,1,"\nEnter (New) email: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_email,msg.body);

	write_msg(cfd,1,1,"\nEnter (New) Address: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_address,msg.body);

	write_msg(cfd,1,2,"\nEnter (New) Password: # ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_password,msg.body);


	bool status=set_student_details(id,&my_student);
	if(status==0)
	{
		write_msg(cfd,0,1,"\nUpdation Failed...");
	}
	else
	{
		write_msg(cfd,0,1,"\nDetails Updated Successfully...");
	}
}


void modify_faculty_details(int cfd)
{
	struct faculty my_faculty;
	struct message msg;
	int readBytes, writeBytes;

	write_msg(cfd,1,0,"\nEnter Faculty-Id: ");
	read_msg(cfd,&msg);
	int id=atoi(msg.body);

	my_faculty=get_faculty_details(id);
	if(my_faculty.faculty_id==-1)
	{
		write_msg(cfd,0,1,"\nInvalid Faculty-Id...");
		return;
	}

	// Getting New Details
	write_msg(cfd,1,1,"\nEnter (New) Name: ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_name,msg.body);

	write_msg(cfd,1,0,"\nEnter (New) Gender: ");	
	read_msg(cfd,&msg);

	my_faculty.faculty_gender=msg.body[0];

	write_msg(cfd,1,1,"\nEnter (New) Phone Number: ");
	read_msg(cfd,&msg);
	
	strcpy(my_faculty.faculty_phone,msg.body);

	write_msg(cfd,1,1,"\nEnter (New) email: ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_email,msg.body);

	write_msg(cfd,1,1,"\nEnter (New) Address: ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_address,msg.body);
	
	write_msg(cfd,1,2,"\nEnter (New) Password: # ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_password,msg.body);


	bool status=set_faculty_details(id,&my_faculty);
	if(status==0)
	{
		write_msg(cfd,0,1,"\nUpdation Failed...");
	}
	else
	{
		write_msg(cfd,0,1,"\nDetails Updated Successfully...");
	}
}


