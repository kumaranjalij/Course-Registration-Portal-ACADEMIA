
void menu(int cfd)
{
    int choice;
    struct message msg;
    char login_id[11];
    char password[11];
    // Creating a Main
    // menu for the user
    begin1:
    wmsg(cfd, 1, 0, "\n\nWELCOME TO ACADMIA : Course Registration System\n\nLogin type : \n1. Faculty\n2. Student\n3. Admin\n4. Exit\n\nENTER YOUR CHOICE : ");
    rmsg(cfd,&msg); 
    choice = atoi(msg.body);
        
    wmsg(cfd, 1, 1, "\nEnter Login ID: ");
    rmsg(cfd,&msg);
    strncpy(login_id, msg.body, 10);
    login_id[10]='\0';

    wmsg(cfd, 1, 2, "\nEnter Password: ");
    rmsg(cfd,&msg);
    strncpy(password, msg.body, 10);
    password[10]='\0';

    switch (choice) {
    case 1:
	login_faculty(cfd, login_id, password);
        goto begin1;
    	break;

    case 2:
        login_student(cfd,  login_id, password);
        goto begin1;
        break;

    case 3:
        login_admin(cfd,  login_id, password);
    	goto begin1;
        break;

    case 4:
    	wmsg(cfd, 0, 0, "");
    	exit(1);
    	break;
    default:
    	wmsg(cfd, 0, 1, "Please enter correct choice ...\n");
       	goto begin1;
    }
}


void student_menu(int cfd, int student_id)
{
    int choice;
    struct message msg;
    // Creating a Main
    // menu for the user
    begin2 :
    wmsg(cfd, 1, 0, "\n\nWELCOME TO STUDENT MENU\n\nAvailable actions : \n1. View Available Courses\n2. Enroll New Course\n3. Drop a Course\n4. View Enrolled Courses\n5. Logout and Exit\n\nENTER YOUR CHOICE : ");
    rmsg(cfd,&msg); 

    choice = atoi(msg.body);
    switch (choice) {
    case 1:
        view_all_course(cfd);
        goto begin2;
        break;

    case 2:
	enroll_course(cfd, student_id);
	goto begin2;
        break;

    case 3:
    	drop_course(cfd, student_id);
        goto begin2;
        break;

    case 4:
    	view_enrolled_course(cfd, student_id);
    	goto begin2;
    	break;

    case 5:
    	wmsg(cfd, 0, 0, "");
    	exit(1);
    	break;

    default:
       	printf("Please enter correct choice...\n");
       	goto begin2;
    }
}

void faculty_menu(int cfd, int faculty_id)
{
    int choice;
    struct message msg;
    // Creating a Main
    // menu for the user
    begin3 :
    wmsg(cfd, 1, 0, "\n\nWELCOME TO FACULTY MENU\n\nAvailable actions : \n1. View Offering Courses\n2. Add New Course\n3. Remove Offered Course\n4. Update Offered Course\n5. Logout and Exit\n\nENTER YOUR CHOICE : ");
    rmsg(cfd,&msg); 

    choice = atoi(msg.body);
    switch (choice) {
    case 1:
        view_offered_course(cfd, faculty_id);
        goto begin3;
        break;

    case 2:
	add_course(cfd, faculty_id);
        goto begin3;
        break;

    case 3:
    	remove_course(cfd, faculty_id);
        goto begin3;
        break;

    case 4:
    	update_course(cfd, faculty_id);
    	goto begin3;
    	break;

    case 5:
    	wmsg(cfd, 0, 0, "");
    	exit(1);
    	break;

    default:
       	printf("Please enter correct choice...\n");
       	goto begin3;
    }
}


void admin_menu(int cfd)
{
    int choice;
    struct message msg;
    // Creating a Main
    // menu for the user
    begin4 :
    wmsg(cfd, 1, 0, "\n\nWELCOME TO ADMIN MENU\n\nAvailable actions : \n1. Add New Student\n2. View Student\n3. Remove Student\n4. Add New Faculty\n5. View Faculty\n6. Remove Faculty\n7. Logout and Exit\n\nENTER YOUR CHOICE : ");
    rmsg(cfd,&msg); 

    choice = atoi(msg.body);
    switch (choice) {
    case 1:
        add_new_student(cfd);
        goto begin4;
        break;

    case 2:
	view_student(cfd);
	goto begin4;
        break;

    case 3:
    	update_student_status(cfd);
    	goto begin4;
        break;

    case 4:
    	add_new_faculty(cfd);
    	goto begin4;
    	break;

    case 5:
	view_faculty(cfd);
	goto begin4;
    	break;

    case 6:
	update_faculty_status(cfd);
    	goto begin4;
    	break;
    
    case 7:
    	wmsg(cfd, 0, 0, "");
    	exit(1);
    	break;
    	
    default:
       	printf("Please enter correct choice...\n");
       	goto begin4;
    }
}


