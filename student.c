#include <stdio.h>
#include <string.h>
#include "student.h"

// File path for student data
#define STUDENT_FILE "students.csv"

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
    printf("Enter age: ");
    scanf("%d", &newStudent.age);
    printf("Enter grade: ");
    scanf("%f", &newStudent.grade);

    fprintf(file, "%d,%s,%d,%.2f\n", newStudent.rollNo, newStudent.name, newStudent.age, newStudent.grade);
    fclose(file);
    printf("Student added successfully.\n");
}

// Function to view all students
void viewStudents() {
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "r");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("\n================== Student Records ==================\n");
    printf("Roll No \t Name \t\t\t Age \t Grade \t\n");
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%d,%f", &student.rollNo, student.name, &student.age, &student.grade);
        printf("%d \t\t %s \t\t %d \t  %.2f\n", student.rollNo, student.name, student.age, student.grade);
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
        sscanf(line, "%d,%[^,],%d,%f", &student.rollNo, student.name, &student.age, &student.grade);
        if (student.rollNo == rollNo) {
            printf("Enter new name: ");
            getchar();  // Clear buffer
            fgets(student.name, 100, stdin);
            student.name[strcspn(student.name, "\n")] = 0;
            printf("Enter new age: ");
            scanf("%d", &student.age);
            printf("Enter new grade: ");
            scanf("%f", &student.grade);
            found = 1;
        }
        fprintf(tempFile, "%d,%s,%d,%.2f\n", student.rollNo, student.name, student.age, student.grade);
    }

    fclose(file);
    fclose(tempFile);

    remove(STUDENT_FILE);
    rename("temp.csv", STUDENT_FILE);

    if (found) {
        printf("Student record updated.\n");
    } else {
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
        sscanf(line, "%d,%[^,],%d,%f", &student.rollNo, student.name, &student.age, &student.grade);
        if (student.rollNo != rollNo) {
            fprintf(tempFile, "%d,%s,%d,%.2f\n", student.rollNo, student.name, student.age, student.grade);
        } else {
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
        sscanf(line, "%d,%[^,],%d,%f", &student.rollNo, student.name, &student.age, &student.grade);
        if (student.rollNo == rollNo) {
            printf("\n================== Search Student Record ================== \n"
                   " Roll No \t\t Name \t\t\t Age \t Grade \n");

            printf(" %d \t\t\t %s \t\t %d \t %.2f\n",
                student.rollNo, student.name, student.age, student.grade);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Student not found.\n");
    }
}
