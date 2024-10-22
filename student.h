#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int rollNo;
    char name[100];
    int age;
    float grade;
};

void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
void searchStudent();

#endif
