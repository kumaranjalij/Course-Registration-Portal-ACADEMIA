/*
Administrator Details maintained like in this structure ...
*/
struct administrator{
int id;
char name[25];
char login_id[10];
char password[10];
};


struct student{
int stud_id;
char stud_name[25];
char stud_gender;
char stud_address[25];
char stud_phone[10];
char stud_email[35];
//Login Credentials
char stud_login_id[11]; // MT2023
char stud_password[11];
int courses[5]; // Course Array of this student.
int n_courses;// number of courses this student selected.
int stud_login_status;
int status;
};

struct faculty{
int faculty_id;
char faculty_name[25];
char faculty_gender;
char faculty_address[25];
char faculty_phone[10];
char faculty_email[35];
char faculty_department[4];
//Login Credentials
char faculty_login_id[11]; // IIITB
char faculty_password[11];
int courses_offered[3]; // Course Array of this faculty.
int n_courses_offered;// number of courses this faculty offered.
int faculty_login_status;
int status;
};

struct message{
int id;
int type;
int action;
char body[1000];
};


struct course{
	int course_id;
	char course_name[5];
	int faculty_id;
	int credits;
	int total_n_seats;
	int avail_n_seats;
	int status;
};

struct record{
	int total_n_students;
	int total_n_faculty;
	int total_n_courses;
	int next_student;
	int next_faculty;
	int next_course;
};
