#include"../headers.h"
#include<stdio.h>
#include<string.h>
#include"../getters_and_setters/get_set_student.h"
#include"../getters_and_setters/get_set_faculty.h"

void add_student(){
    struct student stud;

    char stud_name[100];
    char stud_addr[200];
    int stud_course[6];
    int stud_n_course;
    char stud_login_id[12];
    char stud_password[12];
    int stud_id;
    char stud_email[50];
    int stud_activate_status;


    printf("\n Enter student details \n");
    printf("\n Enter student name: ");
    scanf("%s",stud_name);
    strcpy(stud.stud_name, stud_name);
    printf("\n Enter student address: ");
    scanf("%s",stud_addr);
    strcpy(stud.stud_addr, stud_addr);
    printf("\n Enter student password: ");
    scanf("%s",stud_password);
    strcpy(stud.stud_password, stud_password);
    printf("\n Enter student email: ");
    scanf("%s",stud_password);
    strcpy(stud.stud_email, stud_email);
    printf("\n Enter student activate status: ");
    scanf("%d",stud_activate_status);

    stud.stud_activate_status=1;
    stud.stud_n_course=0;

    set_student(&stud);
}

void add_faculty(){
    struct faculty fac;

    char faculty_name[100];
    int faculty_id;
    char faculty_password[12];
    int courseOffered[5];
    char faculty_addr[200];
    char faculty_email[50];
    char department[20];


    printf("\n Enter faculty details \n");
    printf("\n Enter faculty name: ");
    scanf("%s",faculty_name);
    strcpy(fac.faculty_name, faculty_name);
    printf("\n Enter faculty password: ");
    scanf("%s",faculty_password);
    strcpy(fac.faculty_password, faculty_password);
    printf("\n Enter faculty address: ");
    scanf("%s",faculty_addr);
    strcpy(fac.faculty_addr, faculty_addr);
    printf("\n Enter faculty email: ");
    scanf("%s",faculty_email);
    strcpy(fac.faculty_email, faculty_email);
    printf("\n Enter faculty department: ");
    scanf("%s",department);
    strcpy(fac.department, department);

    set_faculty(&fac);
}