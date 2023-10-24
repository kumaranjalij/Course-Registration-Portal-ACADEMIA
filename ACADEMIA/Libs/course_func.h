
int add_new_course(int cfd, int faculty_id){
	int c_id;
	struct course new_course;
	struct message msg;

	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Name: ");
	rmsg(cfd,&msg);
	strncpy(new_course.c_name,msg.body, sizeof(new_course.c_name));

	new_course.f_id = faculty_id;

	wmsg(cfd, 1, 0, "\nCredits: ");
	rmsg(cfd,&msg);
	new_course.credits = atoi(msg.body);

	wmsg(cfd, 1, 0, "\nTotal seats: ");
	rmsg(cfd,&msg);
	new_course.total_seats = atoi(msg.body);

	new_course.avail_seats = new_course.total_seats;
	new_course.active_status = 1;

	//Initializing...

	//Update to file
	wmsg(cfd, 0, 1, "\nGot Details ...");
	c_id=set_new_course(&new_course);
	if(c_id==-1){
		wmsg(cfd, 0, 1, "\nCannot Save Course...");
		return 0;
	}
	else{
		wmsg2(cfd, 0, 1, "\nCourse Created Successfully!\nNote: \nCourse ID", new_course.c_id);
	}
	return c_id;
}

/*
void view_course_detail(int cfd){
	int course_id;
	struct course cour;
	struct message msg;
	
	//Getting details
	wmsg(cfd, 1, 1, "\nEnter Course ID: ");
	rmsg(cfd,&msg);
	
	course_id = atoi(msg.body);
	cour=get_course(course_id);
	if(cour.c_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get course ...");
		return;
	}
	wmsg3(cfd, 0, 1, "\nCourse name", cour.c_name);
	wmsg2(cfd, 0, 1, "\nCourse faculty ID", cour.f_id);
	wmsg2(cfd, 0, 1, "\nCourse credits", cour.credits);
	wmsg2(cfd, 0, 1, "\nCourse total seats", cour.total_seats);
	wmsg2(cfd, 0, 1, "\nCourse available seats", cour.avail_seats);
	wmsg2(cfd, 0, 1, "\nCourse active status", cour.active_status);
}
*/

int update_course_status(int cfd, int course_id){
	int total_c, total_s;
	struct course cour;
	struct message msg;

	cour=get_course(course_id);
	if(cour.c_id==0){
		wmsg(cfd, 0, 1, "\nUnable to get course ...");
		return -1;
	}
	total_c = get_all_record(2);
	total_s = get_next_record(0);
	if(cour.active_status==1){
		cour.active_status = 0;
		for(int i=1; i<total_s; i++){
			struct student stud = get_student(i);
			if(stud.active_status==1 && stud.course_count>0){
				for(int j=0; j<5; j++){
					if(stud.enrolled_courses[j]==course_id){
						stud.enrolled_courses[j]=0;
						stud.course_count--;
						set_student(i, &stud);
						break;
					}
				}
			}
		}
		int set1 = set_course(course_id, &cour);
		int set2 = set_all_record(2, total_c-1);
		if(set1==1 && set2==1){
			wmsg(cfd, 0, 1, "\nCourse removed");
			return 1;
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nCourse does not exit");
		return -1;
	}
	return -1;
}

void view_all_course(int cfd){
	int total = get_next_record(2);
//	wmsg2(cfd, 0, 1, "Total", total);
	if(total>0){
	//Getting details
		for(int i=1; i<total; i++){
			struct course cour=get_course(i);
			if(cour.active_status==1){
				wmsg2(cfd, 0, 1, "\nCourse", cour.c_id);
				wmsg3(cfd, 0, 1, "", cour.c_name);
			}
		}
	}
	else{
		wmsg(cfd, 0, 1, "\nNo course present");
	}
}
