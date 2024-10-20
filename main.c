#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structures for User and Student
struct User {
    char username[50];
    char password[50];
};

struct Student {
    int rollNo;
    char name[100];
    int age;
    float grade;
};

// File paths for storing data
#define USER_FILE "users.csv"
#define STUDENT_FILE "students.csv"

// Utility functions to handle file I/O for users
void saveUser(struct User user) {
    FILE *file = fopen(USER_FILE, "a");
    if (file != NULL) {
        fprintf(file, "%s,%s\n", user.username, user.password);
        fclose(file);
    }
}

int loginUser(char *username, char *password) {
    FILE *file = fopen(USER_FILE, "r");
    struct User user;

    if (file == NULL) {
        printf("No users registered yet.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%s", user.username, user.password);
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return 1;  // Successful login
        }
    }
    fclose(file);
    return 0;  // Invalid credentials
}

// Functions for login/registration
void registerUser() {
    struct User newUser;
    printf("Enter a username: ");
    scanf("%s", newUser.username);
    printf("Enter a password: ");
    scanf("%s", newUser.password);

    saveUser(newUser);
    printf("Registration successful.\n");
}

void login() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (loginUser(username, password)) {
        printf("Login successful! Welcome, %s.\n", username);
    } else {
        printf("Invalid username or password.\n");
    }
}

// Functions to manage student records
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
    fgets(newStudent.name, 100, stdin);  // Accepts string input with spaces
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;  // Remove newline character
    printf("Enter age: ");
    scanf("%d", &newStudent.age);
    printf("Enter grade: ");
    scanf("%f", &newStudent.grade);

    fprintf(file, "%d,%s,%d,%.2f\n", newStudent.rollNo, newStudent.name, newStudent.age, newStudent.grade);
    fclose(file);
    printf("Student added successfully.\n");
}

void viewStudents() {
    struct Student student;
    FILE *file = fopen(STUDENT_FILE, "r");

    if (file == NULL) {
        printf("No students found.\n");
        return;
    }

    printf("Student Records:\n");
    printf("Roll No \t Name \t\t\t Age \t Grade \t\n");
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^,],%d,%f", &student.rollNo, student.name, &student.age, &student.grade);
        printf("%d \t\t %s \t\t %d \t  %.2f\n", student.rollNo, student.name, student.age, student.grade);
    }
    fclose(file);
}

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
            student.name[strcspn(student.name, "\n")] = 0;  // Remove newline character
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
            printf("\n========== Search Student Record ========== \n"
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

// Main menu and program flow
int main() {
    int choice;

    while (1) {
        printf("\n=============== Student Management System ===============\n");
        printf("\n1. Register\n2. Login\n3. Add Student\n4. View Students\n5. Update Student\n6. Delete Student\n7. Search Student\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                addStudent();
                break;
            case 4:
                viewStudents();
                break;
            case 5:
                updateStudent();
                break;
            case 6:
                deleteStudent();
                break;
            case 7:
                searchStudent();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}

