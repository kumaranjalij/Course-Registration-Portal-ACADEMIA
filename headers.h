/*student structure maintains student details and login credentials*/

struct student
{
	//student details
	int stud_id;
	char stud_name[20];
	char stud_addr[30];
	char stud_email[15];
	
	//login credentials
	char stud_login_id[15]; 
	char stud_passwd[12];
	int courses[5]; //course array-max 5 courses
	int n_courses;	//no. of courses
	int stud_login_status;	
};

/*faculty structure maintains faculty details and login credentials*/

struct faculty
{
	int fac_id;
	char fac_name[20];
	char fac_addr[30];
	char fac_email[20];
	char fac_dept[4];

	//login credentials
	char fac_login_id[10];;
	char fac_passwd[12];
	int courses_offered[3];	//max 3 courses
	int n_courses_offered; //no. of courses offered
	int fac_login_status;
};

/*admin structure contains admin details*/

struct admin
{
	char admin_name[20];
	char login_id[10];
	char passwd[12];
};

/*course structure contains course details*/

struct course
{
	int course_id;
	char course_name[10];
	int faculty_id;
	int credits;
	int total_seats;
	int avail_seats;
};

struct record
{
	int total_stud;
	int total_fac;
	int total_courses;

	int next_stud;
	int next_fac;
	int next_course;
};


