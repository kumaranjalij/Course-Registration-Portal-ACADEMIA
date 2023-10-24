
struct student{
	int s_id;
	char s_name[25];
	char s_gender;
	char s_phone[10];
	char s_email[35];
	char s_login_id[11]; // MT2023
	char s_password[11];
	int enrolled_courses[5];
	int course_count;
	int login_status;
	int active_status;
};

struct faculty{
	int f_id;
	char f_name[25];
	char f_gender;
	char f_phone[10];
	char f_email[35];
	char f_department[3];
	//Login Credentials
	char f_login_id[11]; // IIITB
	char f_password[11];
	int courses[3]; // Course Array of this faculty.
	int course_count;// number of courses this faculty offered.
	int login_status;
	int active_status;
};

/*
Administrator Details maintained like in this structure ...
*/
struct administrator{
	int id;
	char name[25];
	char login_id[11];
	char password[11];
};

struct course{
	int c_id;
	char c_name[5];
	int f_id;
	int credits;
	int total_seats;
	int avail_seats;
	int active_status;
};

struct record{
	int total_student;
	int total_faculty;
	int total_course;
	int new_s;
	int new_f;
	int new_c;
};

struct message{
	int id;
	int type;
	int action;
	char body[1000];
};
