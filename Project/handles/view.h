void view_student_handle(int cfd)
{
	struct student my_student;
	struct message msg;
	int id;
	int readBytes, writeBytes;
	
	write_msg(cfd,1,0,"\nEnter Student-Id: ");
	read_msg(cfd,&msg);

	id=atoi(msg.body);

	my_student=get_student_details(id);
	if(my_student.stud_id==-1)
	{
		write_msg(cfd,0,1,"\nCannot view the Student...");
		return;
	}

	char buffer[1000];
	sprintf(buffer,"...................Student Details..................\nName:  %s\nGender: %c\nAddress: %s\nPhone-number: %s\nEmail: %s\nLogin-Id: %s\nPassword: %s\nNumber of courses enrolled: %d\nCourse ids: %d, %d, %d, %d, %d\n...................End of Statement..................\n",my_student.stud_name,my_student.stud_gender,my_student.stud_address,my_student.stud_phone,my_student.stud_email,my_student.stud_login_id,my_student.stud_password,my_student.n_courses,my_student.courses[0],my_student.courses[1],my_student.courses[2],my_student.courses[3],my_student.courses[4]);
	write_msg(cfd,0,1,buffer);

}

void view_faculty_handle(int cfd)
{
	struct faculty my_faculty;
	struct message msg;
	int id;
	int readBytes, writeBytes;

	write_msg(cfd,1,0,"\nEnter Faculty-Id: ");
	read_msg(cfd,&msg);

	id=atoi(msg.body);

	my_faculty=get_faculty_details(id);
	if(my_faculty.faculty_id==-1)
	{
		write_msg(cfd,0,1,"\nCannot view the Faculty...");
		return;
	}

	char buffer[1000];
	sprintf(buffer,"...................Faculty Details..................\nName:  %s\nGender: %c\nAddress: %s\nPhone-number: %s\nEmail: %s\nDepartment: %s\nLogin-Id: %s\nPassword: %s\nNumber of courses offered: %d\nCourse ids: %d, %d, %d\n...................End of Statement..................\n",my_faculty.faculty_name,my_faculty.faculty_gender,my_faculty.faculty_address,my_faculty.faculty_phone,my_faculty.faculty_email,my_faculty.faculty_department,my_faculty.faculty_login_id,my_faculty.faculty_password,my_faculty.n_courses_offered,my_faculty.courses_offered[0],my_faculty.courses_offered[1],my_faculty.courses_offered[2]);
	write_msg(cfd,0,1,buffer);

}

void view_enrolled_course(int cfd,int student_id)
{
	struct student my_student;
	struct message msg;

	my_student=get_student_details(student_id);
	if(my_student.stud_id==-1)
	{
		write_msg(cfd,0,1,"\nCannot view the Student...");
		return;
	}
	if(my_student.n_courses==0)
	{
		write_msg(cfd,0,1,"\nNo Courses to Enrolled");
		return;
	}

	for(int i=0;i<my_student.n_courses;i++)
	{
		int courses_id=my_student.courses[i];
		write_msg2(cfd,0,1,"\nCourse ID ",courses_id);
	}
	write_msg(cfd,0,1,"\n...................End of Statement..................\n");
}

void view_offering_courses(int cfd,int faculty_id)
{
	struct faculty my_faculty;
	struct message msg;
	
	my_faculty=get_faculty_details(faculty_id);
	if(my_faculty.faculty_id==-1)
	{
		write_msg(cfd,0,1,"\nCannot view the course...");
		return;
	}
	if(my_faculty.n_courses_offered==0)
	{
		write_msg(cfd,0,1,"\nNo Courses Offered");
		return;
	}

	for(int i=0;i<my_faculty.n_courses_offered;i++)
	{
		int courses_id=my_faculty.courses_offered[i];
		write_msg2(cfd,0,1,"\nCourse ID ",courses_id);
	}

	write_msg(cfd,0,1,"\n...................End of Statement..................\n");
}



void add_student_handle(int cfd)
{
	int student_id;
	struct student my_student;
	struct message msg;
	int readBytes, writeBytes;

	//Getting details
	write_msg(cfd,1,1,"\nEnter Name: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_name,msg.body);

	write_msg(cfd,1,0,"\nEnter Gender: ");
	read_msg(cfd,&msg);

	my_student.stud_gender=msg.body[0];

	write_msg(cfd,1,0,"\nEnter Address: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_address,msg.body);
	
	write_msg(cfd,1,0,"\nEnter phone number: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_phone,msg.body);
	
	write_msg(cfd,1,0,"\nEnter email: ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_email,msg.body);
	
	my_student.status=1;


	write_msg(cfd,1,2,"\nEnter Password: # ");
	read_msg(cfd,&msg);

	strcpy(my_student.stud_password,msg.body);

	//Initializing...
	strcpy(my_student.stud_login_id,"");
	my_student.n_courses=0;
	for(int i=0;i<5;i++)
		my_student.courses[i]=-1;
	my_student.stud_login_status=0;

	//Update to file
	student_id=save_student(&my_student);
	if(student_id==-1)
	{
		write_msg(cfd,0,1,"\nCannot Save the Student...");
		return;
	}
	else
	{
		write_msg2(cfd,0,1,"\nStudent Created Successfully!\nNote: Login-Id is MT2023{STUDENT-Id}\nStud-Id. Generated is ",student_id);
	}

	//set Login-Id...
	sprintf(my_student.stud_login_id,"MT2023%d",student_id);
	bool status=set_student_details(student_id,&my_student);
	if(status==0)
	{
		write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
	}
	else
	{
		write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id: MT2023",student_id);
	
	}

}

void view_courses_handle(cfd)
{
	int total_records;
	int i=0;
	struct message msg;
	total_records=get_record_details(0);
	struct course my_course;

	while(i<total_records)
	{
		my_course=get_course_details(i);
		if(my_course.status==1)
		{
			sprintf(msg.body,"%d %s",my_course.course_id, my_course.course_name);
			write_msg(cfd,0,1,msg.body);
			bzero(msg.body,sizeof(msg.body));
		}
		i++;
	}
}

void enroll_course_handle(cfd,id)
{
	struct message msg;
	struct student my_student;
	struct course my_course;
	int course_id;

	write_msg(cfd,1,0,"\nEnter the course id: ");
	read_msg(cfd,&msg);
	course_id=atoi(msg.body);

	my_student=get_student_details(id);
	my_course=get_course_details(course_id);
	
	if(my_course.avail_n_seats>0)
	{
		my_student.courses[my_student.n_courses]=course_id;
		my_student.n_courses=my_student.n_courses+1;
		my_course.avail_n_seats=my_course.avail_n_seats-1;

		if(set_student_details(id,&my_student))
		{
			if(set_course_details(course_id,&my_course))
			{
				bzero(msg.body,sizeof(msg.body));
				write_msg(cfd,0,1,"\nCourse enrolled");
			}
		}
		else
		{
			bzero(msg.body,sizeof(msg.body));
			write_msg(cfd,0,1,"\nNot enrolled");
		}
	}
	else
	{
		bzero(msg.body,sizeof(msg.body));
		write_msg(cfd,0,1,"\nSeats unavailable");
	}
}

void drop_course_handle(cfd,id)
{
	struct message msg;
	struct student my_student;
	struct course my_course;
	int course_id;

	write_msg(cfd,1,0,"\nEnter the course id: ");
	read_msg(cfd,&msg);
	course_id=atoi(msg.body);

	my_student=get_student_details(id);
	my_course=get_course_details(course_id);

	for(int i=0; i<my_student.n_courses;i++)
	{
		if(my_student.courses[i]==course_id)
		{
			my_student.courses[i]=-1;
			my_student.n_courses=my_student.n_courses-1;
			my_course.avail_n_seats=my_course.avail_n_seats+1;
			break;
		}
	}
	if(set_student_details(id,&my_student))
	{
		if(set_course_details(course_id,&my_course))
		{
			bzero(msg.body,sizeof(msg.body));
			write_msg(cfd,0,1,"\nCourse dropped");
		}
	}
	else
	{
		bzero(msg.body,sizeof(msg.body));
		write_msg(cfd,0,1,"\nNot dropeed");
	}
}

void add_new_course_handle(cfd,id)
{
	int course_id;
	struct course my_course;
	struct message msg;
	int readBytes, writeBytes;
	struct faculty my_faculty;

	int total_course=get_record_details(0);
	//Getting details
	write_msg(cfd,1,1,"\nEnter course Name: ");
	read_msg(cfd,&msg);

	strcpy(my_course.course_name,msg.body);

	write_msg(cfd,1,0,"\nEnter faculty id: ");
	read_msg(cfd,&msg);

	my_course.faculty_id=msg.body;

	write_msg(cfd,1,0,"\nEnter credits: ");
	read_msg(cfd,&msg);
	
	my_course.credits=msg.body;

	write_msg(cfd,1,0,"\nEnter total seats: ");
	read_msg(cfd,&msg);

	my_course.total_n_seats=msg.body;

	my_course.avail_n_seats=msg.body;
	my_course.status=1;

	my_faculty=get_faculty_details(id);

	my_faculty.courses_offered[my_faculty.n_courses_offered]=my_course.course_id;

	my_faculty.n_courses_offered= my_faculty.n_courses_offered +1;
	int c = save_course(&my_course);

	bool set1=set_faculty_details(id,&my_faculty);
	
	if(c==-1)
	{
		write_msg(cfd,0,1,"\nCannot Save the course...");
		return;
	}
	else
	{
		write_msg2(cfd,0,1,"\ncourse Created Successfully!\nNote: Id is ",c);
	}

}


void remove_course_handle(cfd,id)
{

	int course_id;
	struct course my_course;
	struct message msg;
	struct student my_student;
	struct faculty my_faculty;
	int total_courses;
	int total_stud;

	total_courses=get_record_details(0);
	total_stud=get_record_details(1);
	my_faculty=get_faculty_details(id);

	write_msg(cfd,1,0,"\nEnter course id: ");
	read_msg(cfd,&msg);
	course_id=atoi(msg.body);

	my_course=get_course_details(course_id);
	my_course.status=0;

	bool set1=set_course_details(course_id,&my_course);
	
	for(int i=0;i<my_faculty.n_courses_offered;i++)
	{
		if(my_faculty.courses_offered[i]=course_id)
		{
			my_faculty.courses_offered[i]=-1;
			my_faculty.n_courses_offered=my_faculty.n_courses_offered-1;
			break;
		}
	}

	bool set2=set_faculty_details(my_faculty.faculty_id,&my_faculty);
	if(set_record_details(0,total_courses-1))
	{
		for(int j=0;j<total_stud;j++)
		{
			int flag=0;
			my_student=get_student_details(j);

			for(int k=0;k<my_student.n_courses;k++)
			{
				if(my_student.courses[k]==course_id)
				{
					my_student.courses[k]=-1;
					my_student.n_courses=my_student.n_courses-1;
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				bool set=set_student_details(my_student.stud_id,&my_student);
			}
		}
		bzero(msg.body,sizeof(msg.body));

	write_msg(cfd,0,1,"\nCourse removed");

	}

}


void add_faculty_handle(int cfd)
{
	int faculty_id;
	struct faculty my_faculty;
	struct message msg;
	int readBytes, writeBytes;

	//Getting details
	write_msg(cfd,1,1,"\nEnter Name: ");
	read_msg(cfd,&msg);
	
	strcpy(my_faculty.faculty_name,msg.body);

	write_msg(cfd,1,0,"\nEnter Gender: ");
	read_msg(cfd,&msg);

	my_faculty.faculty_gender=msg.body[0];

	my_faculty.status=1;

	write_msg(cfd,1,0,"\nEnter Address: ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_address,msg.body);

	write_msg(cfd,1,0,"\nEnter phone number: ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_phone,msg.body);

	write_msg(cfd,1,0,"\nEnter email: ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_email,msg.body);

	write_msg(cfd,1,0,"\nEnter department: ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_department,msg.body);

	write_msg(cfd,1,2,"\nEnter Password: # ");
	read_msg(cfd,&msg);

	strcpy(my_faculty.faculty_password,msg.body);

	//Initializing...
	strcpy(my_faculty.faculty_login_id,"");
	my_faculty.n_courses_offered=0;

	for(int i=0;i<3;i++)
		my_faculty.courses_offered[i]=-1;
	my_faculty.faculty_login_status=0;

	//Update to file
	faculty_id=save_faculty(&my_faculty);
	if(faculty_id==-1)
	{
		write_msg(cfd,0,1,"\nCannot Save the Faculty...");
		return;
	}
	else
	{
		write_msg2(cfd,0,1,"\nFaculty Created Successfully!\nNote: Login-Id is iiitb{Faculty-Id}\nFaculty-Id. Generated is ",faculty_id);
	}

	//set Login-Id...
	sprintf(my_faculty.faculty_login_id,"iiitb%d",faculty_id);
	bool status=set_faculty_details(faculty_id,&my_faculty);
	if(status==0)
	{
		write_msg(cfd,0,1,"\nLogin-Id Setting Failed...");
	}
	else
	{

		write_msg2(cfd,0,1,"\nLogin-Id Settings Completed Successfully... Login-Id: iiitb",faculty_id);
	
	}

}
