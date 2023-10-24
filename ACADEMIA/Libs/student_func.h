
void add_new_student(int cfd){
	int s_id;
	struct student new_stud;
	struct message msg;

	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Name: ");
	rmsg(cfd,&msg);
	strncpy(new_stud.s_name,msg.body, sizeof(new_stud.s_name));

	wmsg(cfd, 1, 0, "\nEnter Gender (M/F): ");
	rmsg(cfd,&msg);
	new_stud.s_gender = msg.body[0];

	wmsg(cfd, 1, 1, "\nEnter phone number: ");
	rmsg(cfd,&msg);
	strncpy(new_stud.s_phone,msg.body,sizeof(new_stud.s_phone));

	wmsg(cfd, 1, 1, "\nEnter email: ");
	rmsg(cfd,&msg);
	strncpy(new_stud.s_email,msg.body,sizeof(new_stud.s_email));

	new_stud.course_count = 0;
	new_stud.active_status = 1;
	new_stud.login_status = 0;
	for(int i=0; i<5; i++){
		new_stud.enrolled_courses[i] = 0;
	}

	//Initializing...
	strcpy(new_stud.s_login_id,"");

	//Update to file
	wmsg(cfd, 0, 1, "\nGot Details ...");
	s_id=set_new_student(&new_stud);
	wmsg2(cfd, 0,1, "ID: ",s_id);
	if(s_id==-1){
		wmsg(cfd, 0, 1, "\nCannot Save Student...");
		return;
	}
	else{
		wmsg3(cfd, 0, 1, "\nStudent Created Successfully!\nNote: \nLogin-Id", new_stud.s_login_id);
		wmsg3(cfd, 0, 1, "\nPassword", new_stud.s_password);
	}
}

void view_student(int cfd){
	int student_id;
	struct student stud;
	struct message msg;
	
	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Login ID: ");
	rmsg(cfd,&msg);
	
	student_id = atoi(msg.body+6);
	stud=get_student(student_id);
	if(stud.s_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get student ...");
		return;
	}
	wmsg3(cfd, 0, 1, "\nStudent name", stud.s_name);
	wmsg3(cfd, 0, 1, "\nStudent phone", stud.s_phone);
	wmsg3(cfd, 0, 1, "\nStudent email", stud.s_email);
	wmsg2(cfd, 0, 1, "\nStudent active status", stud.active_status);
}

void update_student_status(int cfd){
	int student_id, total;
	struct student stud;
	struct message msg;

	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Login ID: ");
	rmsg(cfd,&msg);
	
	student_id = atoi(msg.body+6);
	stud=get_student(student_id);
	if(stud.s_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get student ...");
		return;
	}
	total = get_all_record(0);
	if(stud.active_status==1){
		if(stud.course_count>0){
			for(int i=0; i<5; i++){
				if(stud.enrolled_courses[i]>0){
					struct course cour = get_course(stud.enrolled_courses[i]);
					int course_id = cour.c_id;
					if(cour.active_status==1){
						stud.enrolled_courses[i]=0;
						cour.avail_seats++;
						int set3 = set_course(course_id, &cour);
					}
				}
			}
		}
		stud.active_status = 0;
		int set1 = set_student(student_id, &stud);
		int set2 = set_all_record(0, total-1);
		if(set1==1 && set2==1){
			wmsg(cfd, 0, 1, "\nStudent removed");
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nStudent does not exit");
	}

}

void view_enrolled_course(int cfd, int student_id){
	//int student_id;
	struct student stud;
	struct message msg;
	
	//Getting details
	//wmsg(cfd, 1, 1, "\nEnter Login ID: ");
	//rmsg(cfd,&msg);
	
	//student_id = atoi(msg.body+6);
	stud=get_student(student_id);
	if(stud.s_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get student ...");
		return;
	}
	if(stud.course_count>0){
		for(int i=0; i<5; i++){
			if(stud.enrolled_courses[i]!=0){
				struct course cour = get_course(stud.enrolled_courses[i]);
				wmsg2(cfd, 0, 1, "\n", cour.c_id);
				wmsg3(cfd, 0, 1, " ", cour.c_name);
			}
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nNo Course enrolled");
	}	
	
}

void enroll_course(int cfd, int student_id){
	int course_id;
	struct student stud;
	struct message msg;

	wmsg(cfd, 1, 1, "\nEnter Course ID: ");
	rmsg(cfd,&msg);
	
	course_id=atoi(msg.body);
	
	stud=get_student(student_id);
	if(stud.s_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get student ...");
		return;
	}
	int flag=0;
	for(int j=0; j<5; j++){
		if(stud.enrolled_courses[j]==course_id)
		{
			flag=1;
			break;	
		}
	}
	//wmsg2(cfd, 0, 1, "\ncount", stud.course_count);
	//wmsg2(cfd, 0, 1, "\nid", course_id);
	if(flag==0 && stud.course_count<5){
		for(int i=0; i<5; i++){
			if(stud.enrolled_courses[i]==0){
				struct course cour = get_course(course_id);
				if(cour.c_id==0){
						wmsg(cfd, 0, 1, "\nNo id");
						return;
				}
				else{
				if(cour.avail_seats>0){
					stud.enrolled_courses[i]=course_id;
					stud.course_count++;
					cour.avail_seats--;
					int set1 = set_student(student_id, &stud);
					int set2 = set_course(course_id, &cour);
					if(set1==1 && set2==1){
						wmsg(cfd, 0, 1, "\nCourse enrolled successfully ");
						wmsg2(cfd, 0, 1, "", cour.c_id);
						wmsg3(cfd, 0, 1, " ", cour.c_name);
						return;
					}
					else{
						wmsg(cfd, 0, 1, "\nUnable to update ...");
						return;
					}
				}
				else{
					wmsg(cfd, 0, 1, "\nNo seats available in this course");
					return;
				}
				}
			}
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nCourse already enrolled or cannot enroll more than 5 courses");
		return;
	}	
	
}

void drop_course(int cfd, int student_id){
	int course_id;
	struct student stud;
	struct message msg;

	wmsg(cfd, 1, 1, "\nEnter Course ID: ");
	rmsg(cfd,&msg);
	
	course_id=atoi(msg.body);	
	stud=get_student(student_id);
	if(stud.s_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get student ...");
		return;
	}
	if(stud.course_count>0){
		for(int i=0; i<5; i++){
			if(stud.enrolled_courses[i]==course_id){
				struct course cour = get_course(course_id);
				stud.enrolled_courses[i]=0;
				stud.course_count++;
				cour.avail_seats++;
				int set1 = set_student(student_id, &stud);
				int set2 = set_course(course_id, &cour);
				if(set1==1 && set2==1){
					wmsg(cfd, 0, 1, "\nCourse dropped successfully ");
					wmsg2(cfd, 0, 1, "", cour.c_id);
					wmsg3(cfd, 0, 1, " ", cour.c_name);
					return;
				}
				else{
					wmsg(cfd, 0, 1, "\nUnable to update ...");
					return;
				}
				
			}
			else{
				wmsg(cfd, 0, 1, "\nGiven course not enrolled");
				return;
			}
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nNo course enrolled yet");
		return;
	}	

}

