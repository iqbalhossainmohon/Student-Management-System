//
// Created by iqbal on 22/10/2024.
//

#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int rollNo;
    char name[100];

    char date_of_birth[30];
    char fatherName[100];
    char motherName[100];
    char studentClass[20];
    char address[100];
    char phone[15];
    char gender[20];

    float bangla, english, math, physics, chemistry;
    float cgpa;
};

void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
void searchStudent();

#endif
