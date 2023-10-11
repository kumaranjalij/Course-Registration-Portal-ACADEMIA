//admin authentication
int admin_login(char* logid,char* passwd)
{
	struct admin my_admin;

	my_admin = get_admin_details();
	
	if(strcmp(logid,my_admin.login_id) == 0 && strcmp(passwd,my_admin.passwd) == 0)
		return 1;

	return 0;
}

//student authenticationin
int student_login(char* logid,char* passwd)
{
	struct student my_stud;

	my_stud = get_stud_details(atoi(logid+6));

	if(my_stud.stud_id == -1)
		return 0;
	if(my_stud.stud_login_status == 1) 
		return 0;

	if(strcmp(my_stud.stud_login_id,logid)==0 && strcmp(my_stud.stud_passwd,passwd)==0)
	{
		my_stud.stud_login_status=1;
		set_customer_details(atoi(id+6),&my_stud);
		return 1;
	}
	return 0;
}
