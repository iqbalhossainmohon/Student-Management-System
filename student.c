
#include <stdio.h>
#include <string.h>
#include "student.h"
#include "grading.h"

// File path for student data
#define STUDENT_FILE "students.csv"
#define GRADES_FILE "student_grades.csv"


// Function to add a new student
void addStudent() {
    struct Student newStudent;
    FILE *file = fopen(STUDENT_FILE, "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNo);
    getchar();  // Clear buffer
    printf("Enter student name: ");
    fgets(newStudent.name, 100, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;

    printf("Enter Date of Birth: ");
    scanf("%s", &newStudent.date_of_birth);
    printf("Enter Father Name: ");
    scanf("%s", &newStudent.fatherName);
    printf("Enter Mother Name: ");
    scanf("%s", &newStudent.motherName);
    printf("Enter Class: ");
    scanf("%s", &newStudent.studentClass);
    printf("Enter Address: ");
    scanf("%s", &newStudent.address);
    printf("Enter Phone: ");
    scanf("%s", &newStudent.phone);
    printf("Enter Gender: ");
    scanf("%s", &newStudent.gender);

    printf("Enter marks for Bangla: ");
    scanf("%f", &newStudent.bangla);
    printf("Enter marks for English: ");
    scanf("%f", &newStudent.english);
    printf("Enter marks for Math: ");
    scanf("%f", &newStudent.math);
    printf("Enter marks for Physics: ");
    scanf("%f", &newStudent.physics);
    printf("Enter marks for Chemistry: ");
    scanf("%f", &newStudent.chemistry);

    // Calculate CGPA
    newStudent.cgpa = calculateCGPA(newStudent.bangla, newStudent.english, newStudent.math, newStudent.physics, newStudent.chemistry);

    // Save general info
    fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s,%s\n", newStudent.rollNo, newStudent.name,
            newStudent.date_of_birth, newStudent.fatherName, newStudent.motherName,
            newStudent.studentClass, newStudent.address, newStudent.phone, newStudent.gender);
    fclose(file);

    // Save grades
    file = fopen(GRADES_FILE, "a");
    fprintf(file, "%d,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", newStudent.rollNo, newStudent.name,
            newStudent.bangla, newStudent.english, newStudent.math, newStudent.physics, newStudent.chemistry, newStudent.cgpa);
    fclose(file);

    printf("\nStudent added successfully.\n");
}




// Function to view all students
void viewStudents() {
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "r");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("\t\t\t\t=============== View Student Records ===============\n");
    printf(" ID\t Name \t\t DateOfBirth \t FathersName \t MothersName"
           "\t Class \t Address \t Phone \t\t Gender \n");
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &student.rollNo,
            student.name, &student.date_of_birth, &student.fatherName,
            &student.motherName, &student.studentClass, &student.address, &student.phone, &student.gender);

        printf("%d \t %s \t %s \t %s \t %s \t %s \t %s \t %s \t %s", student.rollNo, student.name,
            student.date_of_birth, student.fatherName, student.motherName, student.studentClass, student.address,
            student.phone, student.gender);
    }
    fclose(file);
}

// Function to update a student's record
void updateStudent() {
    int rollNo, found = 0;
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number of the student to update: ");
    scanf("%d", &rollNo);

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &student.rollNo,
            student.name, &student.date_of_birth, &student.fatherName, &student.motherName,
            &student.studentClass, &student.address, &student.phone, &student.gender);

        if (student.rollNo == rollNo) {
            printf("Enter new name: ");
            getchar();  // Clear buffer
            fgets(student.name, 100, stdin);
            student.name[strcspn(student.name, "\n")] = 0;

            printf("Enter Date of Birth: ");
            scanf("%s", &student.date_of_birth);
            printf("Enter Father Name: ");
            scanf("%s", &student.fatherName);
            printf("Enter Mother Name: ");
            scanf("%s", &student.motherName);
            printf("Enter Your Class: ");
            scanf("%s", &student.studentClass);
            printf("Enter Your Address: ");
            scanf("%s", &student.address);
            printf("Enter Your phone: ");
            scanf("%s", &student.phone);
            printf("Enter Your Gender: ");
            scanf("%s", &student.gender);


            found = 1;
        }
        fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%s,%s,%s", student.rollNo, student.name,
        student.date_of_birth, student.fatherName, student.motherName, student.studentClass,
        student.address, student.phone, student.gender);
    }

    fclose(file);
    fclose(tempFile);

    remove(STUDENT_FILE);
    rename("temp.csv", STUDENT_FILE);

    if (found) {
        printf("Student record updated.\n");
    }
    else {
        printf("Student not found.\n");
    }
}

// Function to delete a student's record
void deleteStudent() {
    int rollNo, found = 0;
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number of the student to delete: ");
    scanf("%d", &rollNo);

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &student.rollNo,
            student.name, &student.date_of_birth, &student.fatherName, &student.motherName,
            &student.studentClass, &student.address, &student.phone, &student.gender);

        if (student.rollNo != rollNo) {
            fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%s,%s,%s", student.rollNo, student.name,
        student.date_of_birth, student.fatherName, student.motherName, student.studentClass,
        student.address, student.phone, student.gender);
        }
        else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(STUDENT_FILE);
    rename("temp.csv", STUDENT_FILE);

    if (found) {
        printf("Student record deleted.\n");
    } else {
        printf("Student not found.\n");
    }
}

// Function to search for a student
void searchStudent() {
    int rollNo, found = 0;
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "r");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &rollNo);

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &student.rollNo,
            student.name, &student.date_of_birth, &student.fatherName, &student.motherName,
            &student.studentClass, &student.address, &student.phone, &student.gender);


        if (student.rollNo == rollNo) {
            printf("\t\t\t=============== View Student Records ===============\n");
            printf(" ID\t Name \t\t DateOfBirth \t FathersName \t MothersName"
           "\t Class \t Address \t Phone \t\t Gender \n");

            printf("%d \t %s \t %s \t %s \t %s \t %s \t %s \t %s \t %s", student.rollNo, student.name,
            student.date_of_birth, student.fatherName, student.motherName, student.studentClass, student.address,
            student.phone, student.gender);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Student not found.\n");
    }
}

