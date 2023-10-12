#include"../headers.h"
#include<stdio.h>
#include<string.h>
#include"../getters_and_setters/get_set_student.h"
#include"../getters_and_setters/get_set_faculty.h"
#include"../getters_and_setters/get_set_course.h"

void view_student(){

    struct student stud;
    int id;
    int rlen, wlen;

    printf("Enter student number");
    scanf("%d", &id);

    stud = get_student_details(id);

    printf("Student name: %s\n", stud.stud_name);
    printf("Student address: %s\n", stud.stud_addr);
    printf("Student login id : %s\n", stud.stud_login_id);
    printf("Student email id : %s\n", stud.stud_email);
    printf("Student id: %d\n", stud.stud_id);
    
}

void view_course(){

    struct course crse;
    int id;

    printf("Enter course number");
    scanf("%d", &id);

    char course_name[20];
    int course_no;
    int no_of_seats;
    int no_of_seats_available;
    int credit;

    crse = get_course(id);

    printf("Course number: %s\n", crse.course_no);
    printf("Course name: %s\n", crse.course_name);
    printf("Number of seats: %s\n", crse.no_of_seats);
    printf("Number of seats available: %s\n", crse.no_of_seats_available);
    printf("Credit: %d\n", crse.credit);
    
}

void view_faculty(){

    struct faculty fac;
    int id;

    printf("Enter faculty number");
    scanf("%d", &id);

        char faculty_name[100];
    int faculty_id;
    char faculty_password[12];
    int courseOffered[5];
    char faculty_addr[200];
    char faculty_email[50];
    char department[20];

    fac = get_faculty(id);

    printf("Faculty name: %s\n", fac.faculty_name);
    printf("Faculty id: %d\n", fac.faculty_id);
    printf("Faculty address: %s\n", fac.faculty_addr);
    printf("Faculty email: %s\n", fac.faculty_email);
    printf("Faculty department : %s\n", fac.department);
    
}