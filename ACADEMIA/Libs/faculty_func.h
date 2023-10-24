
void add_new_faculty(int cfd){
	int f_id;
	struct faculty new_f;
	struct message msg;

	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Name: ");
	rmsg(cfd,&msg);
	strncpy(new_f.f_name,msg.body, sizeof(new_f.f_name));

	wmsg(cfd, 1, 0, "\nEnter Gender (M/F): ");
	rmsg(cfd,&msg);
	new_f.f_gender = msg.body[0];

	wmsg(cfd, 1, 1, "\nEnter phone number: ");
	rmsg(cfd,&msg);
	strncpy(new_f.f_phone,msg.body,sizeof(new_f.f_phone));

	wmsg(cfd, 1, 1, "\nEnter email: ");
	rmsg(cfd,&msg);
	strncpy(new_f.f_email,msg.body,sizeof(new_f.f_email));
	
	wmsg(cfd, 1, 1, "\nEnter department: ");
	rmsg(cfd,&msg);
	strncpy(new_f.f_department,msg.body,sizeof(new_f.f_department));

	new_f.course_count = 0;
	new_f.active_status = 1;
	new_f.login_status = 0;
	for(int i=0; i<3; i++){
		new_f.courses[i] = 0;
	}

	//Initializing...
	strcpy(new_f.f_login_id,"");

	//Update to file
	wmsg(cfd, 0, 1, "\nGot Details ...");
	f_id=set_new_faculty(&new_f);
	wmsg2(cfd, 0,1, "ID: ",f_id);
	if(f_id==-1){
		wmsg(cfd, 0, 1, "\nCannot Save the Faculty...");
		return;
	}
	else{
		wmsg3(cfd, 0, 1, "\nFaculty Created Successfully!\nNote: \nLogin-Id", new_f.f_login_id);
		wmsg3(cfd, 0, 1, "\nPassword", new_f.f_password);
	}
}

void view_faculty(int cfd){
	int faculty_id;
	struct faculty fac;
	struct message msg;
	char dep[3];
	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Login ID: ");
	rmsg(cfd,&msg);
	
	faculty_id = atoi(msg.body+5);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	wmsg3(cfd, 0, 1, "\nFaculty name", fac.f_name);
	wmsg3(cfd, 0, 1, "\nFaculty phone", fac.f_phone);
	wmsg3(cfd, 0, 1, "\nFaculty email", fac.f_email);
	strncpy(dep, fac.f_department, 3);
	wmsg3(cfd, 0, 1, "\nFaculty department", dep);
	wmsg2(cfd, 0, 1, "\nFaculty active status", fac.active_status);
}

void update_faculty_status(int cfd){
	int faculty_id, total, total_c;
	struct faculty fac;
	struct message msg;

	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Login ID: ");
	rmsg(cfd,&msg);
	
	faculty_id = atoi(msg.body+5);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	total = get_all_record(1);
	total_c = get_next_record(2);
	if(fac.active_status==1){
		fac.active_status = 0;
		for(int i=0; i<3; i++){
			for(int j=1; j<total_c; j++){
				struct course cour = get_course(j);
				if(fac.courses[i]==cour.c_id){
					int up = update_course_status(cfd, cour.c_id);
				}
			}
		}
		int set1 = set_faculty(faculty_id, &fac);
		int set2 = set_all_record(1, total-1);
		if(set1==1 && set2==1){
			wmsg(cfd, 0, 1, "\nFaculty removed");
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nFaculty does not exit");
	}

}

void add_course(int cfd, int faculty_id){
	int course_id;
	struct faculty fac;
	struct message msg;

	//Getting details
	//wmsg(cfd, 1, 1, "\nEnter Login ID: ");
	//rmsg(cfd,&msg);
	
	//faculty_id = atoi(msg.body+5);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	if(fac.active_status==1 && fac.course_count<3){
		course_id = add_new_course(cfd, faculty_id);
		if(course_id!=0){
			fac.courses[fac.course_count] = course_id;
			fac.course_count++;
			int set = set_faculty(faculty_id, &fac);		
			if(set == 1){
				wmsg(cfd, 0, 1, "\nDone ... ");
			}
			else{
				wmsg(cfd, 0, 1, "\nUnable to update faculty details");
			}
		}
		else{
			wmsg(cfd, 0, 1, "\nSorry try again");
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nYou have already offered 3 courses... Cannot add more course");
	}
}



void view_offered_course(int cfd, int faculty_id){
	//int faculty_id;
	struct faculty fac;
	struct message msg;
	
	//Getting details
	//wmsg(cfd, 1, 1, "\nEnter Login ID: ");
	//rmsg(cfd,&msg);
	
	//faculty_id = atoi(msg.body+5);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	if(fac.course_count>0){
		int count=1;
		for(int i=0; i<3; i++){
			if(fac.courses[i]>0){
				struct course cour = get_course(fac.courses[i]);
				wmsg2(cfd, 0, 1, "\n\nCourse", count);
				wmsg2(cfd, 0, 1, "\nCourse ID", cour.c_id);
				wmsg3(cfd, 0, 1, "\nCourse name", cour.c_name);
				wmsg2(cfd, 0, 1, "\nCourse credits", cour.credits);
				wmsg2(cfd, 0, 1, "\nCourse total seats", cour.total_seats);
				wmsg2(cfd, 0, 1, "\nCourse available seats", cour.avail_seats);
				wmsg2(cfd, 0, 1, "\nCourse active status", cour.active_status);
				count++;
			}
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nNo Course offered");
	}	
	
}

void remove_course(int cfd, int faculty_id){
	int course_id, total;
	struct faculty fac;
	struct course cour;
	struct message msg;

	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Course ID: ");
	rmsg(cfd,&msg);
	
	course_id = atoi(msg.body);
	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	if(fac.course_count>0){
		for(int i=0; i<3; i++){
			if(fac.courses[i]==course_id){
				fac.courses[i]=0;
				fac.course_count--;
				int up = update_course_status(cfd, course_id);
				int set = set_faculty(faculty_id, &fac);
				if(up==1 && set==1){
					wmsg2(cfd, 0, 1, " ID", course_id);
					return;
				}
			}
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nNo course offered yet");
		return;
	}
	return;
}

void update_course(int cfd, int faculty_id){
	int course_id, seats, total;
	struct faculty fac;
	struct course cour;
	struct message msg;

	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Course ID: ");
	rmsg(cfd,&msg);
	
	course_id = atoi(msg.body);
	
	wmsg(cfd, 1, 1, "\nEnter Updated Seats: ");
	rmsg(cfd,&msg);
	
	seats = atoi(msg.body);

	fac=get_faculty(faculty_id);
	if(fac.f_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get faculty ...");
		return;
	}
	total = get_next_record(0);
	if(fac.course_count>0){
		for(int i=0; i<3; i++){
			if(fac.courses[i]==course_id){
				struct course cour = get_course(course_id);
				if(seats > cour.total_seats && seats > cour.avail_seats){
					cour.avail_seats = cour.avail_seats + (seats - cour.total_seats);
					cour.total_seats = seats;
				}
				else if(seats < cour.total_seats && seats < cour.avail_seats){
					int diff = cour.total_seats - cour.avail_seats;
					cour.avail_seats = seats - diff;
					cour.total_seats = seats;
				}
				else{
					int diff = cour.total_seats - cour.avail_seats;
					diff = diff - seats;
					cour.total_seats = seats;
					cour.avail_seats = 0;
					for(int i=1; i<total; i++){
						if(diff>0){
							struct student stud = get_student(i);
							if(stud.course_count>0){
								for(int j = 0; j<5; j++){
									if(stud.enrolled_courses[j]==course_id){
										stud.enrolled_courses[j]=0;
										stud.course_count--;
										set_student(stud.s_id, &stud);
										diff--;
										break;
									}
								}
							}
						}
						else{
							break;
						}
					}
				}
				int s = set_course(course_id, &cour);
			}

		}
	}
	else{
		wmsg(cfd, 0, 1, "\nNo course offered yet");
		return;
	}
	return;
}

