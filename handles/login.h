//admin login authentication
int admin_login(char* logid, char* passwd)
{
	struct admin ad;

	//get admin credentials
        int fd1;
	fd1 = open("../records/admin.txt", O_RDONLY);
	lseek(fd1, 0, SEEK_SET);
	read(fd1, &ad, sizeof(ad));

	//authentication
	if(strcmp(logid, ad.login_id) == 0 && strcmp(passwd, ad.passwd) == 0)
		return 1;
	
	close(fd1);
	return 0;
}

//student login authentication
int student_login(char* logid,char* password)
{
	struct student stud;

	stud = get_stud_details(atoi(logid+6));

	if(stud.stud_id == -1)
		return 0;

	if(stud.stud_login_status == 1) 
		return 0;

	if(strcmp(stud.stud_login_id, logid) == 0 && strcmp(stud.stud_passwd, password) == 0)
	{
		stud.stud_login_status = 1;
		return 1;
	}
	return 0;
}

//faculty login authentication
int faculty_login(char* logid,char* password)
{
        struct faculty fac;

        fac = get_fac_details(atoi(logid+6));

        if(fac.fac_id == -1)
                return 0;

        if(fac.fac_login_status == 1)
                return 0;

        if(strcmp(fac.fac_login_id, logid) == 0 && strcmp(fac.fac_passwd, password) == 0)
        {
                fac.fac_login_status = 1;
                return 1;
        }
        return 0;
}

//login handle
void login_handle(int ch) 
{
	char logid[20];
	char password[15];

	printf("\nLogin id : ");
	scanf("%s", logid);

	printf("\nPassword : ");
        scanf("%s", password);

	switch(ch)
	{
		case 0: if(admin_login(logid, password))
			{
				printf("\nLogin Successfull..\n");

			}
			else
			{
				printf("\nLogin Failed..\n");
			}




