void admin_menu(int cfd)
{

	struct message msg;
	int readBytes, writeBytes;
	
	begin2:
		write_msg(cfd,1,0,"\n....... Welcome to Admin Menu .......\n1. Add Student\n2. View Student Details\n3. Add Faculty\n4. View Faculty Details\n5. Modify Student Details\n6. Modify Faculty Details\n7. / any key to Exit\nEnter Your Choice: ");
	
	read_msg(cfd,&msg);
	int choice=atoi(msg.body);

	switch(choice)
	{
		case 1: add_student_handle(cfd); 	
			goto begin2;
			break;
		case 2: view_student_handle(cfd); 	
			goto begin2; 
			break;
		case 3: add_faculty_handle(cfd); 	
			goto begin2; 
			break;
		case 4: view_faculty_handle(cfd); 	
			goto begin2; 
			break;
		case 5: modify_student_details(cfd);
			goto begin2; 
			break;
		case 6: modify_faculty_details(cfd);
			goto begin2; 
			break;
		default:
			write_msg(cfd,0,0,"");
			break;
	}

}

void student_menu(int cfd, int id)
{

	struct message msg;
	int readBytes, writeBytes;

	begin3:
	write_msg(cfd,1,0,"\n....... Welcome to Student Menu .......\n1. View All Courses\n2. Enroll (pick) New Course\n3. Drop Course\n4. View Enrolled Course Details\n5. Change Password \n6./ any key to Exit\nEnter Your Choice: ");
	read_msg(cfd,&msg);

	int choice=atoi(msg.body);

	switch(choice)
	{
		case 1: view_courses_handle(cfd); 	
			goto begin3; 
			break;
		case 2: enroll_course_handle(cfd,id); 		
			goto begin3; 
			break;
		case 3: drop_course_handle(cfd,id);
			goto begin3;
			break;
		case 4: view_enrolled_course(cfd,id);
			goto begin3;
			break;
		case 5: modify_student_password(cfd,id);
			goto begin3;
			break;
		
		default:
			struct student my_student;
			my_student=get_student_details(id);
			my_student.stud_login_status=0;
			set_student_details(id,&my_student);
			write_msg(cfd,0,0,"");
			break;
	}

}

void faculty_menu(int cfd, int id)
{

	struct message msg;
	int readBytes, writeBytes;

	begin3:
	write_msg(cfd,1,0,"\n....... Welcome to Faculty Menu .......\n1. View Offering Courses\n2. Add New Course\n3. Remove Course from Catalog\n4. Change Password \n5./ any key to Exit\nEnter Your Choice: ");
	read_msg(cfd,&msg);

	int choice=atoi(msg.body);
	
	switch(choice)
	{
		case 1: view_offering_courses(cfd,id);
			goto begin3;
			break;
		case 2: add_new_course_handle(cfd,id);
			goto begin3;
			break;
		case 3: remove_course_handle(cfd,id);
			goto begin3;
			break;
		case 4: modify_faculty_password(cfd,id);
			goto begin3;
			break;

	default:
	        struct faculty my_faculty;
	        my_faculty=get_faculty_details(id);
	        my_faculty.faculty_login_status=0;
	        set_faculty_details(id,&my_faculty);
	        write_msg(cfd,0,0,"");
	        break;
	}

}

