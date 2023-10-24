
void menu(int cfd);

void login_student(int cfd, char * id, char * pass);

void login_faculty(int cfd, char * id, char * pass);

void login_admin(int cfd, char * id, char * pass);

void student_menu(int cfd, int student_id);

void faculty_menu(int cfd, int faculty_id);

void admin_menu(int cfd);

struct administrator get_admin();


void add_new_student(int cfd);

void view_student(int cfd);

void update_student_status(int cfd);

int set_new_student(struct student *new_stud);

struct student get_student(int student_id);

int set_student(int student_id, struct student *new_stud);

void view_enrolled_course(int cfd, int student_id);

void enroll_course(int cfd, int student_id);

void drop_course(int cfd, int student_id);



void add_new_faculty(int cfd);

void view_faculty(int cfd);

void update_faculty_status(int cfd);

int set_new_faculty(struct faculty *new_f);

struct faculty get_faculty(int faculty_id);

int set_faculty(int faculty_id, struct faculty *new_f);

void add_course(int cfd, int faculty_id);

void view_offered_course(int cfd, int faculty_id);

void remove_course(int cfd, int faculty_id);

void update_course(int cfd, int faculty_id);


int add_new_course(int cfd, int faculty_id);

void view_course_detail(int cfd);

int update_course_status(int cfd, int course_id);

int set_new_course(struct course *new_course);

struct course get_course(int course_id);

int set_course(int course_id, struct course *new_course);

void view_all_course(int cfd);



int get_next_record(int type);

int set_next_record(int type, int next);

int get_all_record(int type);

int set_all_record(int type, int val);

int rmsg(int cfd, struct message* msg);

bool wmsg(int cfd,int type, int action, char* body);

bool wmsg2(int cfd,int type, int action, char* body, int number);

bool wmsg3(int cfd,int type, int action, char* body, char * str);


